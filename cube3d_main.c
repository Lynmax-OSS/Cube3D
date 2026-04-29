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
#include "execution/cub3d.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_scene	scene;
	t_data	*info;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	info = malloc(sizeof(t_data));
	ft_bzero(&scene, sizeof(t_scene));
	parse_file(argv[1], &scene);
	init_info(&scene, info);
	execute_main(info);
	return (0);
}
