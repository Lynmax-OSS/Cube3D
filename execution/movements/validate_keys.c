/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 21:06:05 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:15:22 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	pressed_keys(int keycode, void *param)
{
	t_data	*info;

	info = (t_data *)param;
	if (keycode == FORWARD)
		info->key_fwd = true;
	if (keycode == BACKWARD)
		info->key_bwd = true;
	if (keycode == LEFT)
		info->key_left = true;
	if (keycode == RIGHT)
		info->key_right = true;
	if (keycode == A_LEFT)
		info->key_r_left = true;
	if (keycode == A_RIGHT)
		info->key_r_right = true;
	return (0);
}

int	released_keys(int keycode, void *param)
{
	t_data	*info;

	info = (t_data *)param;
	if (keycode == ESCAPE)
		close_game(info);
	if (keycode == FORWARD)
		info->key_fwd = false;
	if (keycode == BACKWARD)
		info->key_bwd = false;
	if (keycode == RIGHT)
		info->key_right = false;
	if (keycode == LEFT)
		info->key_left = false;
	if (keycode == A_RIGHT)
		info->key_r_right = false;
	if (keycode == A_LEFT)
		info->key_r_left = false;
	return (0);
}
