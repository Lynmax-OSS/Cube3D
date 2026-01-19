/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:12:57 by keteo             #+#    #+#             */
/*   Updated: 2025/12/28 11:12:57 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parser.h"
#include <stdio.h>

static void	print_textures(t_scene *s)
{
	printf("Textures:\n");
	printf("  NO: %s\n", s->no.path);
	printf("  SO: %s\n", s->so.path);
	printf("  WE: %s\n", s->we.path);
	printf("  EA: %s\n", s->ea.path);
}

static void	print_colors(t_scene *s)
{
	printf("Colors:\n");
	printf("  Floor:   %#06X\n", s->floor.value);
	printf("  Ceiling: %#06X\n", s->ceiling.value);
}

static void	print_player(t_scene *s)
{
	printf("Player:\n");
	printf("  Position: (%.1f, %.1f)\n", s->player.x, s->player.y);
	printf("  Direction: %c\n", s->player.dir);
}

void	print_map(t_scene *s)
{
	int	i;

	printf("Map (%d x %d):\n", s->map.width, s->map.height);
	i = 0;
	while (s->map.grid[i])
	{
		printf("%s", s->map.grid[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	ft_bzero(&scene, sizeof(t_scene));
	parse_file(argv[1], &scene);
	print_textures(&scene);
	print_colors(&scene);
	print_player(&scene);
	print_map(&scene);
	printf("\nParsing successful.\n");
	return (0);
}
