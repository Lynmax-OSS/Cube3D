/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:03:36 by jhor              #+#    #+#             */
/*   Updated: 2026/05/02 21:48:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	NE_strafe_left(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferY;
	double	bufferX;

	compute_buffer(&bufferY, (-info->map->player.dirx) * info->movespeed);
	new_Y = (int)(*y + (-info->map->player.dirx) * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += -info->map->player.dirx * info->movespeed;
	compute_buffer(&bufferX, info->map->player.diry * info->movespeed);
	new_X = (int)(*x + info->map->player.diry * info->movespeed + bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += info->map->player.diry * info->movespeed;
}

void	NE_strafe_right(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferY;
	double	bufferX;

	compute_buffer(&bufferY, info->map->player.dirx * info->movespeed);
	new_Y = (int)(*y + info->map->player.dirx * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += info->map->player.dirx * info->movespeed;
	compute_buffer(&bufferX, (-info->map->player.diry) * info->movespeed);
	new_X = (int)(*x + (-info->map->player.diry) * info->movespeed + bufferX);
	if((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += (-info->map->player.diry) * info->movespeed;
}

void	SW_strafe_left(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferY;
	double	bufferX;

	compute_buffer(&bufferY, info->map->player.dirx * info->movespeed);
	new_Y = (int)(*y + info->map->player.dirx * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += info->map->player.dirx * info->movespeed;
	compute_buffer(&bufferX, -info->map->player.diry * info->movespeed);
	new_X = (int)(*x + (-info->map->player.diry) * info->movespeed + bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += (-info->map->player.diry) * info->movespeed;
}

void	SW_strafe_right(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferY;
	double	bufferX;

	compute_buffer(&bufferY, (-info->map->player.dirx) * info->movespeed);
	new_Y = (int)(*y + (-info->map->player.dirx) * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += (-info->map->player.dirx) * info->movespeed;
	compute_buffer(&bufferX, info->map->player.diry * info->movespeed);
	new_X = (int)(*x + info->map->player.diry * info->movespeed + bufferX);
	if((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += info->map->player.diry * info->movespeed;
}
