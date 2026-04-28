/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_renderer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:09:46 by jhor              #+#    #+#             */
/*   Updated: 2026/04/28 23:48:31 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*put_pixel_condition(char type, char *p, t_data *info)
{
	unsigned int	raw;
	int				bytes;

	raw = 0;
	bytes = info->image->bpp / 8;
	p = info->image->data + info->final_y *
		info->image->line_len + info->final_x * bytes;
	if (type == '1')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00FFFFFF);
		*(unsigned int*)p = raw;
	}
	else if (type == '0')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00AABBCC);
		*(unsigned int*)p = raw;
	}
	else if (type == 'N' || type == 'S' || type == 'E' || type == 'W')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00AABBCC);
		*(unsigned int*)p = raw;
	}
	else if (type == 'P')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00AA3366);
		*(unsigned int*)p = raw;
	}
	return (p);
}

void	bpp_condition(char type, int x, int y, t_data *info)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	while (j < info->TILE)
	{
		i = 0;
		while (i < info->TILE)
		{
			if (info->image->bpp == 32)
			{
				info->final_x = x * info->TILE + i;
				info->final_y = y * info->TILE + j;
				if (info->final_x < 0 || info->final_x >= info->image->img_w ||
					info->final_y < 0 || info->final_y >= info->image->img_h)
					return ;
				p = put_pixel_condition(type, p, info);
			}
			i++;
		}
		j++;
	}
}

void	minimap_render(t_data *info)
{
	int		x;
	int		y;

	y = 0;
	while (y < info->map->map.height)
	{
		x = 0;
		while (x < info->map->map.width)
		{
			if (info->map->map.grid[y][x] == '1')
				bpp_condition('1', x, y, info);
			else if (info->map->map.grid[y][x] == '0')
				bpp_condition('0', x, y, info);
			else if (info->map->map.grid[y][x] == 'N'
				|| info->map->map.grid[y][x] == 'E'
				|| info->map->map.grid[y][x] == 'W'
				|| info->map->map.grid[y][x] == 'S')
				bpp_condition(info->map->map.grid[y][x], x, y, info);
			x++;
		}
		y++;
	}
}

void	apply_draw(double x, double y, int TILE, t_data *info)
{
	int	px;
	int	py;

	px = (int)(x * TILE);
	py = (int)(y * TILE);
	if (px < 0 || px >= info->image->img_w ||
		py < 0 || py >= info->image->img_h)
		return ;
	put_pixel(px, py, 0xAA3366, info);
}

void	compute_distance(double hitX, double hitY, t_data *info)
{
	double	steps;
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	i;

	i = 0;
	dx = hitX - info->map->player.x;
	dy = hitY - info->map->player.y;
	if (dx == 0 && dy == 0)
		return ;
	steps = fmax(fabs(dx), fabs(dy)) * 10;
	while (i <= steps)
	{
		x = info->map->player.x + dx * (i / steps);
		y = info->map->player.y + dy * (i / steps);
		apply_draw(x, y, info->TILE, info);
		i++;
	}
}

void	draw_rayline(t_ray *ray, t_data *info)
{
	double	hitX;
	double	hitY;

	hitX = info->map->player.x + (ray->raydirX * ray->perpWallDist);
	hitY = info->map->player.y + (ray->raydirY * ray->perpWallDist);
	compute_distance(hitX, hitY, info);
}

void	draw_ray_in_minimap(t_ray *ray, t_data *info)
{
	double	step;
	int		i;
	int		x;
	double	cameraX;

	step = (double)1280 / (double)60;
	i = 0;
	cameraX = 0;
	while (i < 60)
	{
		x = (int)(i * step);
		ray->raydirX = 0;
		ray->raydirY = 0;
		cameraX = 2 * x / (double)1280 - 1;
		ray->raydirX = info->map->player.dirX + info->planeX * cameraX;
		ray->raydirY = info->map->player.dirY + info->planeY * cameraX;
		raydistance(ray, info);
		draw_rayline(ray, info);
		i++;
	}
}

void	get_img_buffer(void *img, t_data *info)
{
	info->image->data = mlx_get_data_addr(img, &info->image->bpp, 
		&info->image->line_len, &info->image->endian);
	floor_cast(info->horizon, info);
	raydirection(info->ray, info);
	minimap_render(info);
	draw_ray_in_minimap(info->ray, info);
	set_py_in_minimap(info);
}
