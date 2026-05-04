/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:41:00 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:21:00 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	put_pixel(int x, int y, int colour, t_data *info)
{
	char	*dst;

	dst = info->image->data + (y * info->image->line_len + x
			* (info->image->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	calculate_step(int drawstart, int lineheight, t_data *info)
{
	info->step = 1.0 * info->chosen_text->img_height / lineheight;
	info->texpos = (drawstart - 720 / 2 + lineheight / 2) * info->step;
}

void	assign_colour(int *colour, t_text *text, t_data *info)
{
	*colour = *(int *)(text->data
			+ (info->texy * text->line_len + info->texx * (text->bpp / 8)));
}

void	raydirection(t_ray *ray, t_data *info)
{
	int		x;
	double	camerax;

	x = 0;
	camerax = 0;
	while (x < 1280)
	{
		ray->raydirx = 0;
		ray->raydiry = 0;
		camerax = 2 * x / (double)1280 - 1;
		ray->raydirx = info->map->player.dirx + info->planex * camerax;
		ray->raydiry = info->map->player.diry + info->planey * camerax;
		raydistance(ray, info);
		draw_line_stripe(x, ray->perpwalldist, ray, info);
		x++;
	}
}
