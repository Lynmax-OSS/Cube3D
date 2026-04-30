/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_backward.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:11:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 21:11:33 by jhor             ###   ########.fr       */
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
	int		new_Y;
	int		new_X;
	double	bufferX;
	double	bufferY;


	compute_buffer(&bufferY, info->map->player.dirY * info->movespeed);
	new_Y = (int)(*y + info->map->player.dirY * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += info->map->player.dirY * info->movespeed;
	compute_buffer(&bufferX, info->map->player.dirX * info->movespeed);
	new_X = (int)(*x + info->map->player.dirX * info->movespeed + bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += info->map->player.dirX * info->movespeed;
}

void	move_backward(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferX;
	double	bufferY;

	compute_buffer(&bufferY, info->map->player.dirY * info->movespeed);
	new_Y = (int)(*y - info->map->player.dirY * info->movespeed - bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y -= info->map->player.dirY * info->movespeed;
	compute_buffer(&bufferX, info->map->player.dirX * info->movespeed);
	new_X = (int)(*x - info->map->player.dirX * info->movespeed - bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x -= info->map->player.dirX * info->movespeed;
}
