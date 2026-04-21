/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:31:27 by jhor              #+#    #+#             */
/*   Updated: 2026/04/21 22:20:22 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	render(t_data *info)
{
	double	now;
	double	frameTime;

	now = get_time_in_ms();
	frameTime = (now - info->oldTime) / 1000;
	info->acum_time += frameTime;
	info->oldTime = now;
	info->img = mlx_new_image(info->mlx_ptr, 1280, 720);
	get_img_buffer(info->img, info);
	mlx_put_image_to_window(info->mlx_ptr, info->win, info->img, 0, 0);
	mlx_destroy_image(info->mlx_ptr, info->img);
	info->frames++;
	if (info->acum_time >= 1.0)
	{
		// printf("FPS: %d\n", info->frames);
		info->frames = 0;
		info->acum_time -= 1.0;
	}
	info->movespeed = frameTime * 8.0;
	info->rotspeed = frameTime * 3.0;
	return (0);
}
