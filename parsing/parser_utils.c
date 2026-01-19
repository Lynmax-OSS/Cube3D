/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:45:39 by keteo             #+#    #+#             */
/*   Updated: 2026/01/14 16:45:39 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	error_exit(char *msg)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

char *skip_spaces(char *s)
{
    while (*s == ' ' || *s == '\t' || *s == '\n')
        s++;
    return s;
}


int is_empty_line(char *line)
{
    int i = 0;

	if (line == NULL)
		return (1);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (line[i] == '\n' || line[i] == '\0' || line[i] == '\r');
}


int is_map_line(char *line)
{
    int i = 0;

    while (line[i] == ' ' || line[i] == '\t')
        i++;
    if (!ft_strchr("01NSEW", line[i]))
        return (0);
    while (line[i] && line[i] != '\n' && line[i] != '\r')
    {
        if (!ft_strchr("01NSEW ", line[i]))
            return (0);
        i++;
    }
    return (1);
}


void	free_split(char **s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}
