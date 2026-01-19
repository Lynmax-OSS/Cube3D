/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 15:39:33 by keteo             #+#    #+#             */
/*   Updated: 2026/01/07 15:39:33 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_texture	*select_texture(char *id, t_scene *scene)
{
	if (!ft_strncmp(id, "NO", 2))
		return (&scene->no);
	if (!ft_strncmp(id, "SO", 2))
		return (&scene->so);
	if (!ft_strncmp(id, "WE", 2))
		return (&scene->we);
	if (!ft_strncmp(id, "EA", 2))
		return (&scene->ea);
	return (NULL);
}

void	parse_texture(char *line, t_scene *scene)
{
	t_texture	*tex;
	char		*path;

	tex = select_texture(line, scene);
	if (!tex || tex->is_set)
		error_exit("Duplicate or invalid texture");

	path = skip_spaces(line + 2);
	if (!*path)
		error_exit("Missing texture path");

	tex->path = ft_strdup(path);
	tex->is_set = 1;
}
