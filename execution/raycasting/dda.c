/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:09:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:34:58 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	Walldist(t_ray *ray)
{
	if(ray->side == 0) 
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

void	run_dda(int mapX, int mapY, t_ray *ray, t_data *info)
{
	int		hit;

	hit = 0;
	ray->side = 0;
	while (hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			mapX += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			mapY += ray->stepy;
			ray->side = 1;
		}
		if (info->map->map.grid[mapY][mapX] == '1')
			hit = 1;
	}
	Walldist(ray);
}
