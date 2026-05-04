/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_backward.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:11:00 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:00:34 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compute_buffer(double *buffer, double step)
{
	if (step > 0)
		*buffer = +WALL_COLL;
	if (step < 0)
		*buffer = -WALL_COLL;
	if (step == 0)
		*buffer = 0;
}

void	move_forward(char **map, double *x, double *y, t_data *info)
{
	int		new_y;
	int		new_x;
	double	bufferx;
	double	buffery;

	compute_buffer(&buffery, info->map->player.diry * info->movespeed);
	new_y = (int)(*y + info->map->player.diry * info->movespeed + buffery);
	if (new_y >= 0 && new_y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_y])
		&& map[new_y][(int)*x] != '1')
		*y += info->map->player.diry * info->movespeed;
	compute_buffer(&bufferx, info->map->player.dirx * info->movespeed);
	new_x = (int)(*x + info->map->player.dirx * info->movespeed + bufferx);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_x >= 0 && new_x < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_x] != '1')
		*x += info->map->player.dirx * info->movespeed;
}

void	move_backward(char **map, double *x, double *y, t_data *info)
{
	int		new_y;
	int		new_x;
	double	bufferx;
	double	buffery;

	compute_buffer(&buffery, info->map->player.diry * info->movespeed);
	new_y = (int)(*y - info->map->player.diry * info->movespeed - buffery);
	if (new_y >= 0 && new_y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_y])
		&& map[new_y][(int)*x] != '1')
		*y -= info->map->player.diry * info->movespeed;
	compute_buffer(&bufferx, info->map->player.dirx * info->movespeed);
	new_x = (int)(*x - info->map->player.dirx * info->movespeed - bufferx);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_x >= 0 && new_x < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_x] != '1')
		*x -= info->map->player.dirx * info->movespeed;
}
