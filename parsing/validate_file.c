/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 17:39:42 by keteo             #+#    #+#             */
/*   Updated: 2026/01/09 17:39:42 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	validate_scene(t_scene *scene)
{
	if (!scene->no.is_set || !scene->so.is_set
		|| !scene->we.is_set || !scene->ea.is_set)
		error_exit("Missing texture");
	if (!scene->floor.is_set || !scene->ceiling.is_set)
		error_exit("Missing color");
	if (!scene->player.is_set)
		error_exit("Missing player");
	if (!scene->map.grid || scene->map.height == 0)
		error_exit("Missing map");
}
