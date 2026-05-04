/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:31:27 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:17:23 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	get_img_buffer(void *img, t_data *info)
{
	info->image->data = mlx_get_data_addr(img, &info->image->bpp,
			&info->image->line_len, &info->image->endian);
	floor_cast(info->horizon, info);
	raydirection(info->ray, info);
	minimap_render(info);
	draw_ray_in_minimap(info->ray, info);
	set_py_in_minimap(info);
}

int	render(t_data *info)
{
	double	now;
	double	frametime;

	now = get_time_in_ms();
	frametime = (now - info->oldtime) / 1000;
	info->acum_time += frametime;
	info->oldtime = now;
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
	info->movespeed = frametime * 4.0;
	info->rotspeed = frametime * 2.0;
	return (0);
}
