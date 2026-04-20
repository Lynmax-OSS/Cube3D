/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:41:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/20 17:20:24 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//TODO implement the pre-dda prep calculating deltadistX and deltadistY of a single ray, choose which side of the ray to proceed with stepX and stepY

void	put_pixel(int x, int y, int colour, t_data *info)
{
	char	*dst;

	dst = info->image->data + (y * info->image->line_len + x * (info->image->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	assign_colour(int *colour, t_ray *ray)
{
	if (ray->side == 1)
		*colour = 0xAACCBB;
	else
		*colour = 0xFFBBDD;
}

void	draw_line_stripe(int x, double perpWallDist, t_ray *ray, t_data *info)
{
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	colour;
	int	y;

	colour = 0;
	lineHeight = (int)(720 / perpWallDist);
	drawStart = -lineHeight / 2 + 720 / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + 720 / 2;
	if (drawEnd >= 720)
		drawEnd = 720 - 1;
	assign_colour(&colour, ray);
	y = drawStart;
	while (y <= drawEnd)
	{
		put_pixel(x, y, colour, info);
		y++;
	}
}

void	Walldist(double *perpWallDist, t_ray *ray)
{
	if(ray->side == 0) 
		*perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		*perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

double	run_DDA(int mapX, int mapY, t_ray *ray, t_data *info)
{
	int		hit;
	double	perpWallDist;

	hit = 0;
	ray->side = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			mapY += ray->stepY;
			ray->side = 1;
		}
		if (info->map->map.grid[mapY][mapX] > 0)
			hit = 1;
	}
	Walldist(&perpWallDist, ray);
	return (perpWallDist);
}

void	init_step_side(double *perpWallDist, t_ray *ray)
{
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	*perpWallDist = 0.0;
}

double	initial_sidedist(int mapX, int mapY, t_ray *ray, t_data *info)
{
	double	perpWallDist;

	init_step_side(&perpWallDist, ray);
	if (ray->raydirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (info->map->player.x - mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (mapX + 1.0 - info->map->player.x) * ray->deltaDistX;
	}
	if (ray->raydirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (info->map->player.y - mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (mapY + 1.0 - info->map->player.y) * ray->deltaDistY;
	}
	run_DDA(mapX, mapY, ray, info);
	return (perpWallDist);
}

void	init_deltaDist(t_ray *ray)
{
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
}

double	raydistance(t_ray *ray, t_data *info)
{
	int		mapX;
	int		mapY;
	double	perpWallDist;

	mapX = (int)info->map->player.x;
	mapY = (int)info->map->player.y;
	init_deltaDist(ray);
	if (ray->raydirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->raydirX);
	if (ray->raydirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->raydirY);
	perpWallDist = initial_sidedist(mapX, mapY, ray, info);
	return (perpWallDist);
}

void	raydirection(t_ray *ray, t_data *info)
{
	int		x;
	double	cameraX;
	double	perpWallDist;

	x = 0;
	cameraX = 0;
	while (x < 1280)
	{
		ray->raydirX = 0;
		ray->raydirY = 0;
		cameraX = 2 * x / (double)1280 - 1;
		ray->raydirX = info->map->player.dirX + info->planeX *cameraX;
		ray->raydirY = info->map->player.dirY + info->planeY *cameraX;
		perpWallDist = raydistance(ray, info);
		draw_line_stripe(x, perpWallDist, ray, info);
		x++;
	}
}