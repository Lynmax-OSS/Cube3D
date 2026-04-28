/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:37:39 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 01:54:23 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void    draw_fc_texture(int y, t_floor *horizon, t_data *info)
{
    int     x;
    int     cellx;
    int     celly;
    int     tx;
    int     ty;
    int     colour;
    int     ceiling_y;
    t_text  *floor_tex;
    t_text  *ceiling_tex;

    x = 0;
    floor_tex = &info->texture[5];
    ceiling_tex = &info->texture[4];
    while (x < info->image->img_w)
    {
        cellx = (int)horizon->floorx;
        celly = (int)horizon->floory;
        tx = (int)(floor_tex->img_width * (horizon->floorx - cellx))
            & (floor_tex->img_width - 1);
        ty = (int)(floor_tex->img_height * (horizon->floory - celly))
            & (floor_tex->img_height - 1);
        colour = *(int *)(floor_tex->data +
            (ty * floor_tex->line_len + tx * (floor_tex->bpp / 8)));
        put_pixel(x, y, colour, info);
        tx = (int)(ceiling_tex->img_width * (horizon->floorx - cellx))
            & (ceiling_tex->img_width - 1);
        ty = (int)(ceiling_tex->img_height * (horizon->floory - celly))
            & (ceiling_tex->img_height - 1);
        colour = *(int *)(ceiling_tex->data +
            (ty * ceiling_tex->line_len + tx * (ceiling_tex->bpp / 8)));
        ceiling_y = info->image->img_h - 1 - y;
        put_pixel(x, ceiling_y, colour, info);
        horizon->floorx += horizon->floorstepx;
        horizon->floory += horizon->floorstepy;
        ++x;
    }
}

void    floor_cast(t_floor *horizon, t_data *info)
{
    int     y;
    int     p;
    float   posz;

    y = 0;
    while (y < info->image->img_h)
    {
        horizon->raydirx0 = info->map->player.dirX - info->planeX;
        horizon->raydiry0 = info->map->player.dirY - info->planeY;
        horizon->raydirx1 = info->map->player.dirX + info->planeX;
        horizon->raydiry1 = info->map->player.dirY + info->planeY;
        p = y - info->image->img_h / 2;
        posz = 0.5 * info->image->img_h;
        horizon->rowdistance = posz / p;
        horizon->floorstepx = horizon->rowdistance *
            (horizon->raydirx1 - horizon->raydirx0) / info->image->img_w;
        horizon->floorstepy = horizon->rowdistance *
            (horizon->raydiry1 - horizon->raydiry0) / info->image->img_w;
        horizon->floorx = info->map->player.x + horizon->rowdistance *
            horizon->raydirx0;
        horizon->floory = info->map->player.y + horizon->rowdistance *
            horizon->raydiry0;
        draw_fc_texture(y, horizon, info);
        y++;
    }
}
