/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:09:00 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:22:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	walldist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

void	run_dda(int mapx, int mapy, t_ray *ray, t_data *info)
{
	int		hit;

	hit = 0;
	ray->side = 0;
	while (hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			mapy += ray->stepy;
			ray->side = 1;
		}
		if (info->map->map.grid[mapy][mapx] == '1')
			hit = 1;
	}
	walldist(ray);
}
