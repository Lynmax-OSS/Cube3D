/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydistance.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:06:26 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:22:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_step_side(t_ray *ray)
{
	ray->sidedistx = 0;
	ray->sidedisty = 0;
	ray->stepx = 0;
	ray->stepy = 0;
	ray->perpwalldist = 0.0;
}

void	initial_sidedist(int mapx, int mapy, t_ray *ray, t_data *info)
{
	init_step_side(ray);
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (info->map->player.x - mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (mapx + 1.0 - info->map->player.x) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (info->map->player.y - mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (mapy + 1.0 - info->map->player.y) * ray->deltadisty;
	}
	run_dda(mapx, mapy, ray, info);
}

void	init_deltadist(t_ray *ray)
{
	ray->deltadistx = 0;
	ray->deltadisty = 0;
	ray->perpwalldist = 0;
}

void	raydistance(t_ray *ray, t_data *info)
{
	int		mapx;
	int		mapy;

	mapx = (int)info->map->player.x;
	mapy = (int)info->map->player.y;
	init_deltadist(ray);
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	initial_sidedist(mapx, mapy, ray, info);
}
