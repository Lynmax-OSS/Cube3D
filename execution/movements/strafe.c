/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strafe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:03:36 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:14:32 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ne_strafe_left(char **map, double *x, double *y, t_data *info)
{
	int		new_y;
	int		new_x;
	double	buffery;
	double	bufferx;

	compute_buffer(&buffery, (-info->map->player.dirx) * info->movespeed);
	new_y = (int)(*y + (-info->map->player.dirx) * info->movespeed + buffery);
	if (new_y >= 0 && new_y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_y])
		&& map[new_y][(int)*x] != '1')
		*y += -info->map->player.dirx * info->movespeed;
	compute_buffer(&bufferx, info->map->player.diry * info->movespeed);
	new_x = (int)(*x + info->map->player.diry * info->movespeed + bufferx);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_x >= 0 && new_x < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_x] != '1')
		*x += info->map->player.diry * info->movespeed;
}

void	ne_strafe_right(char **map, double *x, double *y, t_data *info)
{
	int		new_y;
	int		new_x;
	double	buffery;
	double	bufferx;

	compute_buffer(&buffery, info->map->player.dirx * info->movespeed);
	new_y = (int)(*y + info->map->player.dirx * info->movespeed + buffery);
	if (new_y >= 0 && new_y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_y])
		&& map[new_y][(int)*x] != '1')
		*y += info->map->player.dirx * info->movespeed;
	compute_buffer(&bufferx, (-info->map->player.diry) * info->movespeed);
	new_x = (int)(*x + (-info->map->player.diry) * info->movespeed + bufferx);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_x >= 0 && new_x < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_x] != '1')
		*x += (-info->map->player.diry) * info->movespeed;
}

void	sw_strafe_left(char **map, double *x, double *y, t_data *info)
{
	int		new_y;
	int		new_x;
	double	buffery;
	double	bufferx;

	compute_buffer(&buffery, info->map->player.dirx * info->movespeed);
	new_y = (int)(*y + info->map->player.dirx * info->movespeed + buffery);
	if (new_y >= 0 && new_y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_y])
		&& map[new_y][(int)*x] != '1')
		*y += info->map->player.dirx * info->movespeed;
	compute_buffer(&bufferx, -info->map->player.diry * info->movespeed);
	new_x = (int)(*x + (-info->map->player.diry) * info->movespeed + bufferx);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_x >= 0 && new_x < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_x] != '1')
		*x += (-info->map->player.diry) * info->movespeed;
}

void	sw_strafe_right(char **map, double *x, double *y, t_data *info)
{
	int		new_y;
	int		new_x;
	double	buffery;
	double	bufferx;

	compute_buffer(&buffery, (-info->map->player.dirx) * info->movespeed);
	new_y = (int)(*y + (-info->map->player.dirx) * info->movespeed + buffery);
	if (new_y >= 0 && new_y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_y])
		&& map[new_y][(int)*x] != '1')
		*y += (-info->map->player.dirx) * info->movespeed;
	compute_buffer(&bufferx, info->map->player.diry * info->movespeed);
	new_x = (int)(*x + info->map->player.diry * info->movespeed + bufferx);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_x >= 0 && new_x < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_x] != '1')
		*x += info->map->player.diry * info->movespeed;
}
