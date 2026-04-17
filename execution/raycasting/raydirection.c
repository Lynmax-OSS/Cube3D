/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:41:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/17 23:34:12 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//TODO implement the pre-dda prep calculating deltadistX and deltadistY of a single ray, choose which side of the ray to proceed with stepX and stepY

void    Walldist(double *perpWallDist, int side, t_ray *ray)
{
    if(side == 0) 
        *perpWallDist = (ray->sideDistX - ray->deltaDistX);
    else
        *perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void    run_DDA(int mapX, int mapY, t_ray *ray, t_data *info)
{
    int     hit;
    int     side;
    double  perpWallDist;

    hit = 0;
    while (hit == 0)
    {
        if (ray->sideDistX < ray->sideDistY)
        {
            ray->sideDistX += ray->deltaDistX;
            mapX += ray->stepX;
            side = 0;
        }
        else
        {
            ray->sideDistY += ray->deltaDistY;
            mapY += ray->stepY;
            side = 1;
        }
        if (info->map->map.grid[mapY][mapX] > 0)
            hit = 1;
    }
    Walldist(&perpWallDist, side, ray);
}

void    init_step_side(t_ray *ray)
{
    ray->sideDistX = 0;
    ray->sideDistY = 0;
    ray->stepX = 0;
    ray->stepY = 0;
}

void    initial_sidedist(int mapX, int mapY, t_ray *ray, t_data *info)
{
    init_step_side(ray);
    if (ray->raydirX < 0)
    {
      ray->stepX = -1;
      ray->sideDistX = (info->map->player.x - mapX) * ray->deltaDistX;
    }
    else
    {
      ray->stepX = 1;
      ray->sideDistX = (mapX + 1.0 - info->map->player.x) * ray->deltaDistX;
    }
    if (ray->raydirY < 0)
    {
      ray->stepY = -1;
      ray->sideDistY = (info->map->player.y - mapY) * ray->deltaDistY;
    }
    else
    {
      ray->stepY = 1;
      ray->sideDistY = (mapY + 1.0 - info->map->player.y) * ray->deltaDistY;
    }
    run_DDA(mapX, mapY, ray, info);
}

void    init_deltaDist(t_ray *ray)
{
    ray->deltaDistX = 0;
    ray->deltaDistY = 0;
}

void    raydistance(t_ray *ray, t_data *info)
{
    int     mapX;
    int     mapY;

    mapX = (int)info->map->player.x;
    mapY = (int)info->map->player.y;
    init_deltaDist(ray);
    if (ray->raydirX == 0)
        ray->deltaDistX = 1e30;
    else
        ray->deltaDistX = fabs(1 / ray->raydirX);
    if (ray->raydirY == 0)
        ray->deltaDistY = 1e30;
    else
        ray->deltaDistY = fabs(1 / ray->raydirY);
    initial_sidedist(mapX, mapY, ray, info);
    
}

void    raydirection(t_ray *ray, t_data *info)
{
    int     x;
    double  cameraX;

    x = 0;
    cameraX = 0;
    while (x < 1280)
    {
        ray->raydirX = 0;
        ray->raydirY = 0;
        cameraX = 2 * x / (double)1280 - 1;
        ray->raydirX = info->map->player.dirX + info->planeX *cameraX;
        ray->raydirY = info->map->player.dirY + info->planeY *cameraX;
        raydistance(ray, info);
        x++;
    }
}