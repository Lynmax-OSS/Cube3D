/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:31:27 by jhor              #+#    #+#             */
/*   Updated: 2026/04/25 23:17:20 by jhor             ###   ########.fr       */
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
	ft_bzero(info->image->data, info->image->line_len * info->image->img_h);
	get_img_buffer(info->img, info);
	mlx_put_image_to_window(info->mlx_ptr, info->win, info->img, 0, 0);
	info->frames++;
	if (info->acum_time >= 1.0)
	{
		printf("FPS: %d\n", info->frames);
		info->frames = 0;
		info->acum_time -= 1.0;
	}
	info->movespeed = frameTime * 4.0;
	info->rotspeed = frameTime * 2.0;
	return (0);
}
