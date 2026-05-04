/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:08:51 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:26:37 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	**init_movement(char **map, double *x, double *y, t_data *info)
{
	*x = 0;
	*y = 0;
	map = info->map->map.grid;
	*x = info->map->player.x;
	*y = info->map->player.y;
	return (map);
}

void	strafe_movement(char **map, double *x, double *y, t_data *info)
{
	if (info->key_right == true)
	{
		if (info->map->player.dir == 'N' || info->map->player.dir == 'E')
			ne_strafe_right(map, x, y, info);
		else
			sw_strafe_right(map, x, y, info);
	}
	if (info->key_left == true)
	{
		if (info->map->player.dir == 'N' || info->map->player.dir == 'E')
			ne_strafe_left(map, x, y, info);
		else
			sw_strafe_left(map, x, y, info);
	}
}

void	rotation_movement(t_data *info)
{
	if (info->key_r_right == true)
	{
		if (info->map->player.dir == 'N' || info->map->player.dir == 'E')
			ne_rotation_right(info);
		else
			sw_rotation_right(info);
	}
	if (info->key_r_left == true)
	{
		if (info->map->player.dir == 'N' || info->map->player.dir == 'E')
			ne_rotation_left(info);
		else
			sw_rotation_left(info);
	}
}

int	apply_movement(void *param)
{
	t_data	*info;
	char	**map;
	double	x;
	double	y;

	map = NULL;
	info = (t_data *)param;
	map = init_movement(map, &x, &y, info);
	if (info->key_fwd == true)
		move_forward(map, &x, &y, info);
	if (info->key_bwd == true)
		move_backward(map, &x, &y, info);
	strafe_movement(map, &x, &y, info);
	rotation_movement(info);
	info->map->player.x = x;
	info->map->player.y = y;
	return (0);
}
