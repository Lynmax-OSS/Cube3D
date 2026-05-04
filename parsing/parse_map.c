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

void	add_line(t_map_buffer **lst, char *line)
{
	t_map_buffer	*new;
	t_map_buffer	*tmp;
	char			*trim;
	char			*expanded;

	new = malloc(sizeof(t_map_buffer));
	if (!new)
		error_exit("Malloc failed");
	trim = ft_strtrim(line, "\r\n");
	expanded = expand_tabs(trim);
	free(trim);
	new->line = expanded;
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

static int	list_size(t_map_buffer *lst)
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

void	check_player(t_scene *scene, char c, int x, int y)
{
	if (scene->player.is_set)
		error_exit("Multiple players");
	scene->player.x = x;
	scene->player.y = y;
	scene->player.dir = c;
	scene->player.is_set = 1;
}

static void	copy_map(t_scene *scene, t_map_buffer *lst)
{
	int	y;
	int	x;
	int	len;

	y = 0;
	while (lst)
	{
		len = ft_strlen(lst->line);
		scene->map.grid[y] = malloc(len + 1);
		if (!scene->map.grid[y])
			error_exit("Malloc failed");
		x = 0;
		while (x < len)
		{
			scene->map.grid[y][x] = lst->line[x];
			check_element(scene, y, x);
			x++;
		}
		scene->map.grid[y][x] = '\0';
		if (x > scene->map.width)
			scene->map.width = x;
		y++;
		lst = lst->next;
	}
	scene->map.grid[y] = NULL;
}

void	parse_map(int fd, char *first, t_scene *scene)
{
	t_map_buffer	*lst;
	t_map_buffer	*tmp;

	lst = NULL;
	add_line(&lst, first);
	store_buffer(lst, fd);
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
