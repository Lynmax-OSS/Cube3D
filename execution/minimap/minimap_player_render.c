/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_player_render.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 22:18:26 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:35:16 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	py_bpp_condition(char type, int player_px, int player_py, t_data *info)
{
	int		i;
	int		j;
	char	*p;
	int		start_x;
	int		start_y;

	start_x = player_px - ((info->tile / 2) / 2);
	start_y = player_py - ((info->tile / 2) / 2);
	j = 0;
	while (j < (info->tile / 2))
	{
		i = 0;
		while (i < (info->tile / 2))
		{
				info->final_x = start_x + i;
				info->final_y = start_y + j;
				if (info->final_x < 0 || info->final_x >= info->image->img_w ||
					info->final_y < 0 || info->final_y >= info->image->img_h)
				   return ;
				p = put_pixel_condition(type, p, info);
			i++;
		}
		j++;
	}
}

void	set_py_in_minimap(t_data *info)
{
	char	**map;
	int		player_px;
	int		player_py;

	map = info->map->map.grid;
	player_px = (int)(info->map->player.x * info->tile);
	player_py = (int)(info->map->player.y * info->tile);
	if (map[(int)info->map->player.y][(int)info->map->player.x] != '1')
		py_bpp_condition('P', player_px, player_py, info);
}
