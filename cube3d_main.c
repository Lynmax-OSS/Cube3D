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

// static void	print_textures(t_scene *s)
// {
// 	printf("Textures:\n");
// 	printf("  NO: %s\n", s->no.path);
// 	printf("  SO: %s\n", s->so.path);
// 	printf("  WE: %s\n", s->we.path);
// 	printf("  EA: %s\n", s->ea.path);
// }

// static void	print_colors(t_scene *s)
// {
// 	printf("Colors:\n");
// 	printf("  Floor:   %#06X\n", s->floor.value);
// 	printf("  Ceiling: %#06X\n", s->ceiling.value);
// }

// static void	print_player(t_scene *s)
// {
// 	printf("Player:\n");
// 	printf("  Position: (%.1f, %.1f)\n", s->player.x, s->player.y);
// 	printf("  Direction: %c\n", s->player.dir);
// }

// void	print_map(t_scene *s)
// {
// 	int	i;

// 	printf("Map (%d x %d):\n", s->map.width, s->map.height);
// 	i = 0;
// 	while (s->map.grid[i])
// 	{
// 		printf("%s\n", s->map.grid[i]);
// 		i++;
// 	}
// }

void	set_py_direction(t_player *player)
{
	if (player->dir == 'N')
	{
		player->dirY = -1;
		player->dirX = 0;
	}
	else if (player->dir == 'S')
	{
		player->dirY = 1;
		player->dirX = 0;
	}
	else if (player->dir == 'E')
	{
		player->dirY = 0;
		player->dirX = 1;
	}
	else if (player->dir == 'W')
	{
		player->dirY = 0;
		player->dirX = -1;
	}
}

void	set_plane(t_player *player, t_data *info)
{
	if (player->dir == 'N' || player->dir == 'S')
	{
		info->planeX = 0.66;
		info->planeY = 0;
	}
	else
	{
		info->planeX = 0;
		info->planeY = 0.66;
	}
}

void	set_key_bool(t_data *info)
{
	info->key_fwd = false;
	info->key_bwd = false;
	info->key_right = false;
	info->key_left = false;
	info->key_r_right = false;
	info->key_r_left = false;
}

void	set_ray_variables(t_ray *ray)
{
	ray->raydirX = 0;
	ray->raydirY = 0;
}

void	load_fc_textures(t_text *texture, t_data *info)
{
	texture[4].img = mlx_xpm_file_to_image(info->mlx_ptr, 
			"textures/xpm_converted/ceiling.xpm", 
		&texture[4].img_width, &texture[4].img_height);
	texture[4].data = mlx_get_data_addr(texture[4].img, &texture[4].bpp,
		&texture[4].line_len, &texture[4].endian);
	texture[5].img = mlx_xpm_file_to_image(info->mlx_ptr, 
			"textures/xpm_converted/floor.xpm", 
		&texture[5].img_width, &texture[5].img_height);
	texture[5].data = mlx_get_data_addr(texture[5].img, &texture[5].bpp,
		&texture[5].line_len, &texture[5].endian);
}

void	load_textures(t_text *texture, t_data *info)
{
	texture[0].img = mlx_xpm_file_to_image(info->mlx_ptr, 
			"textures/xpm_converted/gray_stone.xpm", 
		&texture[0].img_width, &texture[0].img_height);
	texture[0].data = mlx_get_data_addr(texture[0].img, &texture[0].bpp,
		&texture[0].line_len, &texture[0].endian);
	texture[1].img = mlx_xpm_file_to_image(info->mlx_ptr, 
		"textures/xpm_converted/red_brick.xpm", 
		&texture[1].img_width, &texture[1].img_height);
	texture[1].data = mlx_get_data_addr(texture[1].img, &texture[1].bpp,
			&texture[1].line_len, &texture[1].endian);
	texture[2].img = mlx_xpm_file_to_image(info->mlx_ptr, 
		"textures/xpm_converted/white_brick.xpm", 
		&texture[2].img_width, &texture[2].img_height);
	texture[2].data = mlx_get_data_addr(texture[2].img, &texture[2].bpp,
			&texture[2].line_len, &texture[2].endian);
	texture[3].img = mlx_xpm_file_to_image(info->mlx_ptr, 
		"textures/xpm_converted/wood.xpm", 
		&texture[3].img_width, &texture[3].img_height);
	texture[3].data = mlx_get_data_addr(texture[3].img, &texture[3].bpp,
			&texture[3].line_len, &texture[3].endian);
	load_fc_textures(texture, info);
}

void	init_info_extend(t_data *info)
{
	info->chosen_text = NULL;
	info->horizon = malloc(sizeof(t_floor));
}

void	init_info(t_scene *scene, t_data *info)
{
	info->TILE = 10;
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
	// print_textures(&scene);
	// print_colors(&scene);
	// print_player(&scene);
	// print_map(&scene);
	// printf("\nParsing successful.\n");
	// printf("image width:%d\n", info->image->img_w);
	// printf("image heigh:%d\n", info->image->img_h);
	execute_main(info);
	return (0);
}
