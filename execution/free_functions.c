/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 00:32:48 by jhor              #+#    #+#             */
/*   Updated: 2026/05/01 01:07:37 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_textures(t_data *info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		mlx_destroy_image(info->mlx_ptr, info->texture[i].img);
		i++;
	}
}

void	free_grid(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	free(map->grid);
}

void	free_scene(t_data *info)
{
	if (info->map->no.path)
		free(info->map->no.path);
	if (info->map->so.path)
		free(info->map->so.path);
	if (info->map->we.path)
		free(info->map->we.path);
	if (info->map->ea.path)
		free(info->map->ea.path);
	if (info->map->map.grid)
		free_grid(&info->map->map);
}
