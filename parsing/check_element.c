/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 15:42:37 by keteo             #+#    #+#             */
/*   Updated: 2026/05/04 15:45:45 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	check_element(t_scene *scene, int y, int x)
{
	if (ft_strchr("NSEW", scene->map.grid[y][x]))
		check_player(scene, scene->map.grid[y][x], x, y);
	else if (!ft_strchr("01 \t", scene->map.grid[y][x]))
		error_exit("Invalid map character");
}
