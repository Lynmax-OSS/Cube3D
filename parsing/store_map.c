/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 17:35:18 by keteo             #+#    #+#             */
/*   Updated: 2026/04/30 19:11:51 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	store_map(t_mline *lst, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (!line || (line[0] == '\n' || line[0] == '\r' || line[0] == '\0'))
			error_exit("Empty line inside map");
		add_line(&lst, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}
