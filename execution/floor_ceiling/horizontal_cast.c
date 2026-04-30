/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_cast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 23:37:39 by jhor              #+#    #+#             */
/*   Updated: 2026/05/01 01:05:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// void    fc_put_colour(int x, int y, t_text *text, t_data *info)
// {
//     int cellx;
//     int celly;
//     int tx;
//     int ty;
//     int colour;

//     cellx = (int)info->horizon->floorx;
//     celly = (int)info->horizon->floory;
//     tx = (int)(text->img_width * (info->horizon->floorx - cellx))
//             & (text->img_width - 1);
//     ty = (int)(text->img_height * (info->horizon->floory - celly))
//             & (text->img_height - 1);
//     colour = *(int *)(text->data +
//         (ty * text->line_len + tx * (text->bpp / 8)));
//     put_pixel(x, y, colour, info);
// }

void    draw_fc_colour(int y, t_floor *horizon, t_data *info)
{
    int     x;

    x = 0;
    while (x < info->image->img_w)
    {
        put_pixel(x, y, info->map->floor.value, info);        
        put_pixel(x, info->image->img_h - 1 - y,
            info->map->ceiling.value, info);
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
        horizon->raydirx0 = info->map->player.dirX - info->planex;
        horizon->raydiry0 = info->map->player.dirY - info->planey;
        horizon->raydirx1 = info->map->player.dirX + info->planex;
        horizon->raydiry1 = info->map->player.dirY + info->planey;
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
        draw_fc_colour(y, horizon, info);
        y++;
    }
}
