/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extension_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keteo <keteo@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 10:48:05 by keteo             #+#    #+#             */
/*   Updated: 2025/12/28 10:48:05 by keteo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

int extension_check(char *filepath)
{
	int path_len;

	path_len = ft_strlen(filepath);
	if (!ft_strrchr(filepath, '.'))
		ft_printf("Error:Invalid file\n");
	else if (ft_strncmp(filepath + path_len - 3, "cub", 3) == 0) 
		return (1);
	return (0);
}