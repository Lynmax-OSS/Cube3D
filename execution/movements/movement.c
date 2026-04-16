/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:03:36 by jhor              #+#    #+#             */
/*   Updated: 2026/04/16 16:45:01 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	compute_buffer(double *buffer, double step)
{
	if (step > 0)
		*buffer = +WALL_COLL;
	if (step < 0)
		*buffer = -WALL_COLL;
	if (step == 0)
		*buffer = 0;
}

void	strafe_left(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferY;
	double	bufferX;

	compute_buffer(&bufferY, (-info->map->player.dirX * info->movespeed));
	new_Y = (int)(*y + (-info->map->player.dirX * info->movespeed) + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += -info->map->player.dirX * info->movespeed;
	compute_buffer(&bufferX, info->map->player.dirY * info->movespeed);
	new_X = (int)(*x + info->map->player.dirY * info->movespeed + bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += info->map->player.dirY * info->movespeed;
}

void	strafe_right(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferY;
	double	bufferX;

	compute_buffer(&bufferY, info->map->player.dirX * info->movespeed);
	new_Y = (int)(*y + info->map->player.dirX * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += info->map->player.dirX * info->movespeed;
	compute_buffer(&bufferX, (-info->map->player.dirY * info->movespeed));
	new_X = (int)(*x + (-info->map->player.dirY * info->movespeed) + bufferX);
	if((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += -info->map->player.dirY * info->movespeed;
}

//How does the player move ? Does it move in by changing the signature of the player on the grid map ? 
//Or are we gonna find the direction of the player facing, calculate the distance moved by movespeed * direction to get the coordinate of the player destination ?

void	move_forward(char **map, double *x, double *y, t_data *info)
{
	int		new_Y;
	int		new_X;
	double	bufferX;
	double	bufferY;


	compute_buffer(&bufferY, info->map->player.dirY * info->movespeed);
	new_Y = (int)(*y + info->map->player.dirY * info->movespeed + bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y += info->map->player.dirY * info->movespeed;
	compute_buffer(&bufferX, info->map->player.dirX * info->movespeed);
	new_X = (int)(*x + info->map->player.dirX * info->movespeed + bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x += info->map->player.dirX * info->movespeed;
}

void	move_backward(char **map, double *x, double *y, t_data *info)
{
	int	new_Y;
	int	new_X;
	double	bufferX;
	double	bufferY;

	compute_buffer(&bufferY, info->map->player.dirY * info->movespeed);
	new_Y = (int)(*y - info->map->player.dirY * info->movespeed - bufferY);
	if (new_Y >= 0 && new_Y < info->map->map.height
		&& (int)*x >= 0 && (int)*x < (int)ft_strlen(map[new_Y])
		&& map[new_Y][(int)*x] != '1')
		*y -= info->map->player.dirY * info->movespeed;
	compute_buffer(&bufferX, info->map->player.dirX * info->movespeed);
	new_X = (int)(*x - info->map->player.dirX * info->movespeed - bufferX);
	if ((int)*y >= 0 && (int)*y < info->map->map.height
		&& new_X >= 0 && new_X < (int)ft_strlen(map[(int)*y])
		&& map[(int)*y][new_X] != '1')
		*x -= info->map->player.dirX * info->movespeed;
}

char    **init_movement(char **map, double *x, double *y, t_data *info)
{
    *x = 0;
    *y = 0;
    map = info->map->map.grid;
    *x = info->map->player.x;
    *y = info->map->player.y;
    return (map);
}

int	apply_movement(void *param)
{
	t_data	*info;
    char    **map;
    double  x;
    double  y;

	map = NULL;
	info = (t_data *)param;
	map = init_movement(map, &x, &y, info);
	if(info->key_fwd == true)
		move_forward(map, &x, &y, info);
	if(info->key_bwd == true)
		move_backward(map, &x, &y, info);
	if(info->key_right == true)
		strafe_right(map, &x, &y, info);
	if(info->key_left == true)
		strafe_left(map, &x, &y, info);
	if(info->key_r_right == true)
		rotation_right(info);
	if(info->key_r_left == true)
		rotation_left(info);
	info->map->player.x = x;
	info->map->player.y = y;
	return (0);
}

int	pressed_keys(int keycode, void *param)
{
	t_data	*info;

	info = (t_data *)param;
	if(keycode == FORWARD)
		info->key_fwd = true;
	if(keycode == BACKWARD)
		info->key_bwd = true;
	if(keycode == LEFT)
		info->key_left = true;
	if(keycode == RIGHT)
		info->key_right = true;
	if(keycode == A_LEFT)
		info->key_r_left = true;
	if(keycode == A_RIGHT)
		info->key_r_right = true;
	return (0);
}

int	released_keys(int keycode, void *param)
{
	t_data	*info;

	info = (t_data *)param;
	if (keycode == ESCAPE)
		close_game(info);
	if(keycode == FORWARD)
		info->key_fwd = false;
	if(keycode == BACKWARD)
		info->key_bwd = false;
	if(keycode == RIGHT)
		info->key_right = false;
	if(keycode == LEFT)
		info->key_left = false;
	if(keycode == A_RIGHT)
		info->key_r_right = false;
	if(keycode == A_LEFT)
		info->key_r_left = false;
	return (0);
}
