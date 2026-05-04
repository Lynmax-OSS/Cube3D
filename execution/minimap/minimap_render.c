/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 16:09:46 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 15:58:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*minimap_player_condition(char type, char *p, t_data *info)
{
	unsigned int	raw;

	raw = 0;
	if (type == 'P')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00AA3366);
		*(unsigned int *)p = raw;
	}
	return (p);
}

char	*put_pixel_condition(char type, char *p, t_data *info)
{
	unsigned int	raw;
	int				bytes;

	raw = 0;
	bytes = info->image->bpp / 8;
	p = info->image->data + info->final_y
		* info->image->line_len + info->final_x * bytes;
	if (type == '1')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00FFFFFF);
		*(unsigned int *)p = raw;
	}
	else if (type == '0')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00AABBCC);
		*(unsigned int *)p = raw;
	}
	else if (type == 'N' || type == 'S' || type == 'E' || type == 'W')
	{
		raw = (unsigned int)mlx_get_color_value(info->mlx_ptr, 0x00AABBCC);
		*(unsigned int *)p = raw;
	}
	minimap_player_condition(type, p, info);
	return (p);
}

void	bpp_condition(char type, int x, int y, t_data *info)
{
	int		i;
	int		j;
	char	*p;

	j = 0;
	while (j < info->tile)
	{
		i = 0;
		while (i < info->tile)
		{
			if (info->image->bpp == 32)
			{
				info->final_x = x * info->tile + i;
				info->final_y = y * info->tile + j;
				if (info->final_x < 0 || info->final_x >= info->image->img_w
					|| info->final_y < 0 || info->final_y >= info->image->img_h)
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
		while (x < info->map->map.width
			&& info->map->map.grid[y][x] != '\0')
		{
			if (info->map->map.grid[y][x] == '1')
				bpp_condition('1', x, y, info);
			else if (info->map->map.grid[y][x] == '0')
				bpp_condition('0', x, y, info);
			else if ((info->map->map.grid[y][x] == 'N'
				|| info->map->map.grid[y][x] == 'E'
				|| info->map->map.grid[y][x] == 'W'
				|| info->map->map.grid[y][x] == 'S'))
				bpp_condition(info->map->map.grid[y][x], x, y, info);
			x++;
		}
		y++;
	}
}
