/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tabs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 20:44:17 by keteo             #+#    #+#             */
/*   Updated: 2026/04/30 20:44:17 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_tab(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			count++;
		i++;
	}
	return (count);
}

static char	*replace_tabs(char *dst)
{
	*dst++ = ' ';
	*dst++ = ' ';
	*dst++ = ' ';
	*dst++ = ' ';
	return (dst);
}

char	*expand_tabs(char *line)
{
	int		i;
	int		tab_count;
	char	*new;
	char	*dst;

	tab_count = count_tab(line);
	if (tab_count == 0)
		return (ft_strdup(line));
	new = malloc(ft_strlen(line) + (tab_count * 3) + 1);
	if (!new)
		error_exit("Malloc failed");
	i = 0;
	dst = new;
	while (line[i])
	{
		if (line[i] == '\t')
			dst = replace_tabs(dst);
		else
			*dst++ = line[i];
		i++;
	}
	*dst = '\0';
	return (new);
}
