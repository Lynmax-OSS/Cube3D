/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 16:53:50 by jhor              #+#    #+#             */
/*   Updated: 2026/04/21 22:06:54 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*list of components for rendering
-raycasting (raydirection, delta distance, dda algorithm)
-calculate frameTime and convert it into fps, redraw and clear image buffer
-movements using mlx_hook
*/

int	close_game(t_data *info)
{
	mlx_destroy_window(info->mlx_ptr, info->win);
	exit (EXIT_SUCCESS);
}

int	game_loop(void *param)
{
	t_data	*info;

	info = (t_data *)param;
	apply_movement(info);
	render(info);
	return (0);
}

void	execute_main(t_data *info)
{
	mlx_hook(info->win, DestroyNotify, SubstructureNotifyMask, close_game, info);
	mlx_hook(info->win, KeyPress, KeyPressMask, pressed_keys, info);
	mlx_hook(info->win, KeyRelease, KeyReleaseMask, released_keys, info);
	mlx_loop_hook(info->mlx_ptr, game_loop, info);
	mlx_loop(info->mlx_ptr);
}