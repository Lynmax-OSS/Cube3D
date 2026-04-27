/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:35:18 by keteo             #+#    #+#             */
/*   Updated: 2026/04/27 17:52:11 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	store_map(t_mline *lst, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_empty_line(line))
			error_exit("Empty line inside map");
		add_line(&lst, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
