/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:41:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/16 20:54:56 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//TODO implement the pre-dda prep calculating deltadistX and deltadistY of a single ray, choose which side of the ray to proceed with stepX and stepY

void    raydirection(t_ray *ray, t_data *info)
{
    int     x;
    double  cameraX;

    x = 0;
    cameraX = 0;
    while (x < 1280)
    {
        cameraX = 2 * x / (double)1280 - 1;
        ray->raydirX = info->map->player.dirX + info->planeX *cameraX;
        ray->raydirY = info->map->player.dirY + info->planeY *cameraX;
        x++;
    }
}