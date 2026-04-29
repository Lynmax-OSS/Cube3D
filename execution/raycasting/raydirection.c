/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raydirection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 18:41:00 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:37:45 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

//TODO implement the pre-dda prep calculating deltadistx and deltadisty of a single ray, choose which side of the ray to proceed with stepx and stepy

void	put_pixel(int x, int y, int colour, t_data *info)
{
	char	*dst;

	dst = info->image->data + (y * info->image->line_len + x * (info->image->bpp / 8));
	*(unsigned int *)dst = colour;
}

void	calculate_step(int drawstart, int lineheight, t_data *info)
{
	info->step = 1.0 * info->chosen_text->img_height / lineheight;
	info->texpos = (drawstart - 720 / 2 + lineheight / 2) * info->step;
}

void	assign_colour(int *colour, t_text *text, t_data *info)
{
	*colour = *(int *)(text->data +
		(info->texy * text->line_len +
		info->texx * (text->bpp / 8)));
}

void	raydirection(t_ray *ray, t_data *info)
{
	int		x;
	double	cameraX;

	x = 0;
	cameraX = 0;
	while (x < 1280)
	{
		ray->raydirx = 0;
		ray->raydiry = 0;
		cameraX = 2 * x / (double)1280 - 1;
		ray->raydirx = info->map->player.dirX + info->planex * cameraX;
		ray->raydiry = info->map->player.dirY + info->planey * cameraX;
		raydistance(ray, info);
		draw_line_stripe(x, ray->perpwalldist, ray, info);
		x++;
	}
}
