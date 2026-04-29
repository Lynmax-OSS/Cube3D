/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 22:12:33 by jhor              #+#    #+#             */
/*   Updated: 2026/04/29 22:33:06 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_text	*pick_texture(t_text *texture, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydirx > 0)
			return (&texture[0]);
		return (&texture[1]);
	}
	if (ray->raydiry > 0)
		return (&texture[2]);
	return (&texture[3]);
}

void	find_text(double pwd, t_ray *ray, t_data *info)
{
	double	wallx;

	info->texx = 0;
	info->chosen_text = pick_texture(info->texture, ray);
	wallx = 0;
	if (ray->side == 0)
		wallx = info->map->player.y + (pwd * ray->raydiry);
	else
		wallx = info->map->player.x + (pwd * ray->raydirx);
	wallx -= floor(wallx);
	info->texx = (int)(wallx * (double)info->chosen_text->img_width);
	if (ray->side == 0 && ray->raydirx > 0)
		info->texx = info->chosen_text->img_width - info->texx - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		info->texx = info->chosen_text->img_width - info->texx - 1;
}
