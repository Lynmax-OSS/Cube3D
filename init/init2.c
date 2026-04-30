/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:43:02 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:49:33 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/cub3d.h"

void	set_py_direction(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dirY = -1;
		player->dirX = 0;
	}
	else if (player->dir == 'S')
	{
		player->dirY = 1;
		player->dirX = 0;
	}
	else if (player->dir == 'E')
	{
		player->dirY = 0;
		player->dirX = 1;
	}
	else if (player->dir == 'W')
	{
		player->dirY = 0;
		player->dirX = -1;
	}
}

void	set_plane(t_player *player, t_data *info)
{
	if (player->dir == 'N' || player->dir == 'S')
	{
		info->planex = 0.66;
		info->planey = 0;
	}
	else
	{
		info->planex = 0;
		info->planey = 0.66;
	}
}

void	set_key_bool(t_data *info)
{
	info->key_fwd = false;
	info->key_bwd = false;
	info->key_right = false;
	info->key_left = false;
	info->key_r_right = false;
	info->key_r_left = false;
}

void	set_ray_variables(t_ray *ray)
{
	ray->raydirx = 0;
	ray->raydiry = 0;
}
