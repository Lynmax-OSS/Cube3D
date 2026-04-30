/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:42:10 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:49:22 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/cub3d.h"

void	init_info_extend(t_data *info)
{
	info->chosen_text = NULL;
	info->horizon = malloc(sizeof(t_floor));
}

void	init_info(t_scene *scene, t_data *info)
{
	info->tile = 10;
	info->map = scene;
	info->img = NULL;
	info->oldTime = get_time_in_ms();
	info->movespeed = 0;
	info->rotspeed = 0;
	info->image = malloc(sizeof(t_img));
	info->image->bpp = 0;
	info->image->endian = 0;
	info->image->line_len = 0;
	info->image->img_h = 720;
	info->image->img_w = 1280;
	info->image->data = NULL;
	info->mlx_ptr = mlx_init();
	info->win = mlx_new_window(info->mlx_ptr, 1280, 720, "Cub3d");
	info->img = mlx_new_image(info->mlx_ptr, 1280, 720);
	set_py_direction(&(info->map->player));
	set_plane(&(info->map->player), info);
	set_key_bool(info);
	info->acum_time = 0.0;
	info->frames = 0;
	info->ray = malloc(sizeof(t_ray));
	set_ray_variables(info->ray);
	load_textures(info->texture, info);
	init_info_extend(info);
}
