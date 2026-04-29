/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 20:01:51 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:37:45 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    SW_rotation_left(t_data *info)
{
    double  oldDirX;
    double  oldplanex;

    oldDirX = info->map->player.dirX;
    info->map->player.dirX = info->map->player.dirX * 
        cos(info->rotspeed) - info->map->player.dirY * sin(info->rotspeed);
    info->map->player.dirY = oldDirX * 
        sin(info->rotspeed) + info->map->player.dirY * cos(info->rotspeed);
    oldplanex = info->planex;
    info->planex = info->planex * 
        cos(info->rotspeed) - info->planey * sin(info->rotspeed);
    info->planey = oldplanex * 
        sin(info->rotspeed) + info->planey * cos(info->rotspeed);
}

void    SW_rotation_right(t_data *info)
{
    double  oldDirX;
    double  oldplanex;

    oldDirX = info->map->player.dirX;
    info->map->player.dirX = info->map->player.dirX * 
        cos(-info->rotspeed) - info->map->player.dirY * sin(-info->rotspeed);
    info->map->player.dirY = oldDirX * 
        sin(-info->rotspeed) + info->map->player.dirY * cos(-info->rotspeed);
    oldplanex = info->planex;
    info->planex = info->planex * 
        cos(-info->rotspeed) - info->planey * sin(-info->rotspeed);
    info->planey = oldplanex * 
        sin(-info->rotspeed) + info->planey * cos(-info->rotspeed);
}

void    NE_rotation_left(t_data *info)
{
    double  oldDirX;
    double  oldplanex;

    oldDirX = info->map->player.dirX;
    info->map->player.dirX = info->map->player.dirX * 
        cos(-info->rotspeed) - info->map->player.dirY * sin(-info->rotspeed);
    info->map->player.dirY = oldDirX * 
        sin(-info->rotspeed) + info->map->player.dirY * cos(-info->rotspeed);
    oldplanex = info->planex;
    info->planex = info->planex * 
        cos(-info->rotspeed) - info->planey * sin(-info->rotspeed);
    info->planey = oldplanex * 
        sin(-info->rotspeed) + info->planey * cos(-info->rotspeed);
}

void    NE_rotation_right(t_data *info)
{
    double  oldDirX;
    double  oldplanex;

    oldDirX = info->map->player.dirX;
    info->map->player.dirX = info->map->player.dirX * 
        cos(info->rotspeed) - info->map->player.dirY * sin(info->rotspeed);
    info->map->player.dirY = oldDirX * 
        sin(info->rotspeed) + info->map->player.dirY * cos(info->rotspeed);
    oldplanex = info->planex;
    info->planex = info->planex * 
        cos(info->rotspeed) - info->planey * sin(info->rotspeed);
    info->planey = oldplanex * 
        sin(info->rotspeed) + info->planey * cos(info->rotspeed);
}
