/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:22:52 by keteo             #+#    #+#             */
/*   Updated: 2026/01/14 16:22:52 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	flood(char **m, int x, int y, t_map *map)
{
	if (y < 0 || x < 0 || y >= map->height
		|| x >= (int)ft_strlen(m[y]))
		error_exit("Map not closed");
	if (m[y][x] == ' ' || m[y][x] == '\0')
		error_exit("Map not closed");
	if (m[y][x] == '1' || m[y][x] == 'V')
		return ;
	m[y][x] = 'V';
	flood(m, x + 1, y, map);
	flood(m, x - 1, y, map);
	flood(m, x, y + 1, map);
	flood(m, x, y - 1, map);
}

static char	**copy_map(char **src)
{
	char	**copy;
	int		i;

	i = 0;
	while (src[i])
		i++;
	copy = malloc(sizeof(char *) * (i + 1));
	if (!copy)
		error_exit("Malloc failed");
	i = 0;
	while (src[i])
	{
		copy[i] = ft_strdup(src[i]);
		if (!copy[i])
			error_exit("Malloc failed");
		i++;
	}
	copy[i] = NULL;
	return (copy);
}


void	validate_map(t_scene *scene)
{
	char	**copy;
	int		i;

	copy = copy_map(scene->map.grid);
	flood(copy, scene->player.x, scene->player.y, &scene->map);
	i = 0;
	while (copy[i])
		free(copy[i++]);
	free(copy);
}
