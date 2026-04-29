/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_ray_render.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:41:29 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:37:45 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	apply_draw(double x, double y, int tile, t_data *info)
{
	int	px;
	int	py;

	px = (int)(x * tile);
	py = (int)(y * tile);
	if (px < 0 || px >= info->image->img_w ||
		py < 0 || py >= info->image->img_h)
		return ;
	put_pixel(px, py, 0xAA3366, info);
}

void	compute_distance(double hitX, double hitY, double i, t_data *info)
{
	double	steps;
	double	x;
	double	y;
	double	dx;
	double	dy;

	dx = hitX - info->map->player.x;
	dy = hitY - info->map->player.y;
	if (dx == 0 && dy == 0)
		return ;
	steps = fmax(fabs(dx), fabs(dy)) * 10;
	while (i <= steps)
	{
		x = info->map->player.x + dx * (i / steps);
		y = info->map->player.y + dy * (i / steps);
		apply_draw(x, y, info->tile, info);
		i++;
	}
}

void	draw_rayline(t_ray *ray, t_data *info)
{
	double	hitX;
	double	hitY;
    double  i;

    i = 0;
	hitX = info->map->player.x + (ray->raydirx * ray->perpwalldist);
	hitY = info->map->player.y + (ray->raydiry * ray->perpwalldist);
	compute_distance(hitX, hitY, i, info);
}

void	draw_ray_in_minimap(t_ray *ray, t_data *info)
{
	double	step;
	int		i;
	int		x;
	double	cameraX;

	step = (double)1280 / (double)60;
	i = 0;
	cameraX = 0;
	while (i < 60)
	{
		x = (int)(i * step);
		ray->raydirx = 0;
		ray->raydiry = 0;
		cameraX = 2 * x / (double)1280 - 1;
		ray->raydirx = info->map->player.dirX + info->planex * cameraX;
		ray->raydiry = info->map->player.dirY + info->planey * cameraX;
		raydistance(ray, info);
		draw_rayline(ray, info);
		i++;
	}
}
