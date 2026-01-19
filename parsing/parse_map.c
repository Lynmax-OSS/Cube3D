/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:10:19 by keteo             #+#    #+#             */
/*   Updated: 2026/01/14 17:10:19 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

typedef struct s_mline
{
	char			*line;
	struct s_mline	*next;
}	t_mline;

static void	add_line(t_mline **lst, char *line)
{
	t_mline	*new;
	t_mline	*tmp;
	char *trim;

	new = malloc(sizeof(t_mline));
	if (!new)
		error_exit("Malloc failed");
	trim = ft_strtrim(line, "\r");
	new->line = trim;
	// ft_printf("%s", new->line);
	new->next = NULL;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static int	list_size(t_mline *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

static void	check_player(t_scene *scene, char c, int x, int y)
{
	if (scene->player.is_set)
		error_exit("Multiple players");
	scene->player.x = x;
	scene->player.y = y;
	scene->player.dir = c;
	scene->player.is_set = 1;
}

static void	copy_map(t_scene *scene, t_mline *lst)
{
	int	y;
	int	x;

	y = 0;
	while (lst)
	{
		scene->map.grid[y] = ft_strtrim(lst->line, "\r\n\t ");
		if (!scene->map.grid[y])
			error_exit("Malloc failed");
		x = 0;
		while (scene->map.grid[y][x])
		{
			if (ft_strchr("NSEW", scene->map.grid[y][x]))
				check_player(scene, scene->map.grid[y][x], x, y);
			else if (!ft_strchr("01", scene->map.grid[y][x]))
				error_exit("Invalid map character");
			x++;
		}
		if (x > scene->map.width)
			scene->map.width = x;
		y++;
		lst = lst->next;
	}
	scene->map.grid[y] = NULL;
}

void	parse_map(int fd, char *first, t_scene *scene)
{
	t_mline	*lst;
	t_mline	*tmp;
	char	*line;

	lst = NULL;
	add_line(&lst, first);
	while ((line = get_next_line(fd)))
	{
		if (is_empty_line(line))
			error_exit("Empty line inside map");
		add_line(&lst, line);
	}
	scene->map.height = list_size(lst);
	scene->map.width = 0;
	scene->map.grid = malloc(sizeof(char *) * (scene->map.height + 1));
	if (!scene->map.grid)
		error_exit("Malloc failed");
	copy_map(scene, lst);
	while (lst)
	{
		tmp = lst->next;
		free(lst->line);
		free(lst);
		lst = tmp;
	}
}
