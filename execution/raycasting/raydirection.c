/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:41:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/28 23:33:38 by jhor             ###   ########.fr       */
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

t_text	*pick_texture(t_text *texture, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydirX > 0)
			return (&texture[0]);
		return (&texture[1]);
	}
	if (ray->raydirY > 0)
		return (&texture[2]);
	return (&texture[3]);
}

void	find_text(double pwd, t_ray *ray, t_data *info)
{
	double	wallx;

	info->texx = 0;
	info->chosen_text = pick_texture(info->texture, ray);
	wallx = 0;
	if (ray->side == 0)
		wallx = info->map->player.y + (pwd * ray->raydirY);
	else
		wallx = info->map->player.x + (pwd * ray->raydirX);
	wallx -= floor(wallx);
	info->texx = (int)(wallx * (double)info->chosen_text->img_width);
	if (ray->side == 0 && ray->raydirX > 0)
		info->texx = info->chosen_text->img_width - info->texx - 1;
	if (ray->side == 1 && ray->raydirY < 0)
		info->texx = info->chosen_text->img_width - info->texx - 1;
}

void	calculate_step(int drawstart, int lineheight, t_data *info)
{
	info->step = 1.0 * info->chosen_text->img_height / lineheight;
	info->texpos = (drawstart - 720 / 2 + lineheight / 2) * info->step;
}

void	assign_colour(int *colour, t_text *text, t_data *info)
{
	*colour = *(int *)(text->data +
		(info->texy * text->line_len +
		info->texx * (text->bpp / 8)));
}

void	draw_line_stripe(int x, double perpWallDist, t_ray *ray, t_data *info)
{
	int		lineHeight;
	int		drawstart;
	int		drawend;
	int		y;
	int		colour;

	lineHeight = (int)(720 / perpWallDist);
	drawstart = -lineHeight / 2 + 720 / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineHeight / 2 + 720 / 2;
	if (drawend >= 720)
		drawend = 720 - 1;
	find_text(ray->perpWallDist, ray, info);
	calculate_step(drawstart, lineHeight, info);
	y = drawstart;
	while (y <= drawend)
	{
		info->texy = (int)info->texpos & (info->chosen_text->img_height - 1);
		info->texpos += info->step;
		assign_colour(&colour, info->chosen_text, info);
		put_pixel(x, y, colour, info);
		y++;
	}
}

void	Walldist(t_ray *ray)
{
	if(ray->side == 0) 
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void	run_DDA(int mapX, int mapY, t_ray *ray, t_data *info)
{
	int		hit;

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
		if (info->map->map.grid[mapY][mapX] == '1')
			hit = 1;
	}
	Walldist(ray);
}

void	init_step_side(t_ray *ray)
{
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->perpWallDist = 0.0;
}

void	initial_sidedist(int mapX, int mapY, t_ray *ray, t_data *info)
{
	init_step_side(ray);
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
}

void	init_deltaDist(t_ray *ray)
{
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->perpWallDist = 0;
}

void	raydistance(t_ray *ray, t_data *info)
{
	int		mapX;
	int		mapY;

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
	initial_sidedist(mapX, mapY, ray, info);
}

void	raydirection(t_ray *ray, t_data *info)
{
	int		x;
	double	cameraX;

	x = 0;
	cameraX = 0;
	while (x < 1280)
	{
		ray->raydirX = 0;
		ray->raydirY = 0;
		cameraX = 2 * x / (double)1280 - 1;
		ray->raydirX = info->map->player.dirX + info->planeX * cameraX;
		ray->raydirY = info->map->player.dirY + info->planeY * cameraX;
		raydistance(ray, info);
		draw_line_stripe(x, ray->perpWallDist, ray, info);
		x++;
	}
}
