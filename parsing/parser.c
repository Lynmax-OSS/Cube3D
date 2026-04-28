/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:30:18 by keteo             #+#    #+#             */
/*   Updated: 2025/12/28 11:30:18 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "parser.h"

static int	extension_check(char *map)
{
	int	path_len;

	path_len = ft_strlen(map);
	if (!ft_strrchr(map, '.'))
		ft_printf("Error:Invalid file\n");
	else if (ft_strncmp(map + path_len - 3, "cub", 3) == 0)
		return (1);
	return (0);
}

// void	parse_file(char *path, t_scene *scene)
// {
// 	int		fd;
// 	char	*line;

// 	if (!extension_check(path))
// 		error_exit("Invalid file extension");

// 	fd = open(path, O_RDONLY);
// 	if (fd < 0)
// 		error_exit("Cannot open file");

// 	while ((line = get_next_line(fd)))
// 	{
// 		if (is_empty_line(line))
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		if (is_map_line(line))
// 		{
// 			parse_map(fd, line, scene);
// 			print_map(scene);
// 			break ;
// 		}
// 		line = skip_spaces(line);
// 		printf("%s", line);
// 		if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
// 			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
// 			parse_texture(line, scene);
// 		else if (*line == 'F' || *line == 'C')
// 			parse_color(line, scene);
// 		else if (is_map_line(line))
// 			error_exit("Unknown identifier");
// 		free(line);
// 	}
// 	close(fd);
// 	validate_scene(scene);
// 	validate_map(scene);
// }

static void	free_line(char *line, char *trimmed)
{
	free(line);
	free(trimmed);
}

static void	check_textures(char *trimmed, t_scene *scene)
{
	if (!ft_strncmp(trimmed, "NO", 2) || !ft_strncmp(trimmed, "SO", 2)
		|| !ft_strncmp(trimmed, "WE", 2) || !ft_strncmp(trimmed, "EA", 2))
		parse_texture(trimmed, scene);
	else if (*trimmed == 'F' || *trimmed == 'C')
		parse_color(trimmed, scene);
	else
		error_exit("Unknown identifier");
}

char	*check_line(char *line, t_scene *scene, int fd, int *map_checked)
{
	char	*trimmed;

	trimmed = ft_strtrim(line, "\r\n \t");
	printf("%s\n", trimmed);
	if (is_empty_line(trimmed))
	{
		free_line(line, trimmed);
		return (get_next_line(fd));
	}
	if (is_map_line(trimmed))
	{
		parse_map(fd, line, scene);
		free_line(line, trimmed);
		*map_checked = 1;
		return (NULL);
	}
	check_textures(trimmed, scene);
	free_line(line, trimmed);
	return (get_next_line(fd));
}

void	parse_file(char *path, t_scene *scene)
{
	int		fd;
	char	*line;
	int		map_checked;

	map_checked = 0;
	if (!extension_check(path))
		error_exit("Invalid file extension");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		error_exit("Cannot open file");
	line = get_next_line(fd);
	while (line != NULL && !map_checked)
	{
		line = check_line(line, scene, fd, &map_checked);
	}
	close(fd);
	validate_scene(scene);
	validate_map(scene);
}
