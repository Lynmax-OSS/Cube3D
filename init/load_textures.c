/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:45:01 by jhor              #+#    #+#             */
/*   Updated: 2026/05/02 19:55:05 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/cub3d.h"

void	load_textures(t_text *texture, t_data *info)
{
	texture[0].img = mlx_xpm_file_to_image(info->mlx_ptr,
		info->map->ea.path, &texture[0].img_width, &texture[0].img_height);
	texture[0].data = mlx_get_data_addr(texture[0].img, &texture[0].bpp,
		&texture[0].line_len, &texture[0].endian);
	texture[1].img = mlx_xpm_file_to_image(info->mlx_ptr,
		info->map->we.path, &texture[1].img_width, &texture[1].img_height);
	texture[1].data = mlx_get_data_addr(texture[1].img, &texture[1].bpp,
			&texture[1].line_len, &texture[1].endian);
	texture[2].img = mlx_xpm_file_to_image(info->mlx_ptr,
		info->map->no.path, &texture[2].img_width, &texture[2].img_height);
	texture[2].data = mlx_get_data_addr(texture[2].img, &texture[2].bpp,
			&texture[2].line_len, &texture[2].endian);
	texture[3].img = mlx_xpm_file_to_image(info->mlx_ptr,
		info->map->so.path, &texture[3].img_width, &texture[3].img_height);
	texture[3].data = mlx_get_data_addr(texture[3].img, &texture[3].bpp,
			&texture[3].line_len, &texture[3].endian);
}
