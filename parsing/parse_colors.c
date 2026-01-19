/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:10:12 by keteo             #+#    #+#             */
/*   Updated: 2026/01/14 17:10:12 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	parse_rgb(char *s)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(s, ',');
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		error_exit("Invalid RGB format");
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_split(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("RGB out of range");
	return ((r << 16) | (g << 8) | b);
}

void	parse_color(char *line, t_scene *scene)
{
	char	*data;

	data = skip_spaces(line + 1);
	if (*line == 'F')
	{
		if (scene->floor.is_set)
			error_exit("Duplicate floor color");
		scene->floor.value = parse_rgb(data);
		scene->floor.is_set = 1;
	}
	else if (*line == 'C')
	{
		if (scene->ceiling.is_set)
			error_exit("Duplicate ceiling color");
		scene->ceiling.value = parse_rgb(data);
		scene->ceiling.is_set = 1;
	}
}
