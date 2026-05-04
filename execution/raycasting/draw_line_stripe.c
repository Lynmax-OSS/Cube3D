/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_stripe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:10:12 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:18:35 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_line_stripe(int x, double perpwalldist, t_ray *ray, t_data *info)
{
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		y;
	int		colour;

	lineheight = (int)(720 / perpwalldist);
	drawstart = -lineheight / 2 + 720 / 2;
	if (drawstart < 0)
		drawstart = 0;
	drawend = lineheight / 2 + 720 / 2;
	if (drawend >= 720)
		drawend = 720 - 1;
	find_text(ray->perpwalldist, ray, info);
	calculate_step(drawstart, lineheight, info);
	y = drawstart;
	while (y <= drawend)
	{
		info->texy = (int)info->texpos & (info->chosen_text->img_height - 1);
		info->texpos += info->step;
		assign_colour(&colour, info->chosen_text, info);
		put_pixel(x, y, colour, info);
		y++;
	}
}
