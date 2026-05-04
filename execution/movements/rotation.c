/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:01:51 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:13:51 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	sw_rotation_left(t_data *info)
{
	double	oldirx;
	double	oldplanex;

	oldirx = info->map->player.dirx;
	info->map->player.dirx = info->map->player.dirx
		* cos(info->rotspeed) - info->map->player.diry * sin(info->rotspeed);
	info->map->player.diry = oldirx
		* sin(info->rotspeed) + info->map->player.diry * cos(info->rotspeed);
	oldplanex = info->planex;
	info->planex = info->planex
		* cos(info->rotspeed) - info->planey * sin(info->rotspeed);
	info->planey = oldplanex
		* sin(info->rotspeed) + info->planey * cos(info->rotspeed);
}

void	sw_rotation_right(t_data *info)
{
	double	oldirx;
	double	oldplanex;

	oldirx = info->map->player.dirx;
	info->map->player.dirx = info->map->player.dirx
		* cos(-info->rotspeed) - info->map->player.diry * sin(-info->rotspeed);
	info->map->player.diry = oldirx
		* sin(-info->rotspeed) + info->map->player.diry * cos(-info->rotspeed);
	oldplanex = info->planex;
	info->planex = info->planex
		* cos(-info->rotspeed) - info->planey * sin(-info->rotspeed);
	info->planey = oldplanex
		* sin(-info->rotspeed) + info->planey * cos(-info->rotspeed);
}

void	ne_rotation_left(t_data *info)
{
	double	oldirx;
	double	oldplanex;

	oldirx = info->map->player.dirx;
	info->map->player.dirx = info->map->player.dirx
		* cos(-info->rotspeed) - info->map->player.diry * sin(-info->rotspeed);
	info->map->player.diry = oldirx
		* sin(-info->rotspeed) + info->map->player.diry * cos(-info->rotspeed);
	oldplanex = info->planex;
	info->planex = info->planex
		* cos(-info->rotspeed) - info->planey * sin(-info->rotspeed);
	info->planey = oldplanex
		* sin(-info->rotspeed) + info->planey * cos(-info->rotspeed);
}

void	ne_rotation_right(t_data *info)
{
	double	oldirx;
	double	oldplanex;

	oldirx = info->map->player.dirx;
	info->map->player.dirx = info->map->player.dirx
		* cos(info->rotspeed) - info->map->player.diry * sin(info->rotspeed);
	info->map->player.diry = oldirx
		* sin(info->rotspeed) + info->map->player.diry * cos(info->rotspeed);
	oldplanex = info->planex;
	info->planex = info->planex
		* cos(info->rotspeed) - info->planey * sin(info->rotspeed);
	info->planey = oldplanex
		* sin(info->rotspeed) + info->planey * cos(info->rotspeed);
}
