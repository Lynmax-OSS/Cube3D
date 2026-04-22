/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_render.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:18:26 by jhor              #+#    #+#             */
/*   Updated: 2026/04/22 22:02:42 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	py_bpp_condition(char type, t_data *info)
{
	int		i;
	int		j;
	char	*p;
	int		py_TILE;
	int		start_x;
	int		start_y;
	int		player_px;
	int		player_py;

	py_TILE = 5;
	player_px = (int)(info->map->player.x * info->TILE);
	player_py = (int)(info->map->player.y * info->TILE);
	start_x = player_px - (py_TILE / 2);
	start_y = player_py - (py_TILE / 2);
	j = 0;
	while (j < py_TILE)
	{
		i = 0;
		while (i < py_TILE)
		{
			if (info->image->bpp == 32)
			{
				info->final_x = start_x + i;
				info->final_y = start_y + j;
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

void	set_py_in_minimap(t_data *info)
{
	char	**map;

	map = info->map->map.grid;
	if (map[(int)info->map->player.y][(int)info->map->player.x] != '1')
		py_bpp_condition('P', info);
}
