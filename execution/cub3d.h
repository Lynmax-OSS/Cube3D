/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:32:25 by jhor              #+#    #+#             */
/*   Updated: 2026/04/14 19:06:01 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include "../parsing/parser.h"
# include <math.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <stdbool.h>

#define ESCAPE XK_Escape
#define FORWARD XK_w
#define BACKWARD XK_s
#define LEFT XK_a
#define RIGHT XK_d
#define A_LEFT XK_Left
#define A_RIGHT XK_Right

typedef struct s_img
{
	int 	img_w;
	int		img_h;
	int		bpp;
	int		line_len;
	int		endian;
	char	*data;
} t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win;
	void		*img;
	double		oldTime;
	double		movespeed;
	double		rotspeed;
	t_img		*image;
	t_scene		*map;
	int			TILE;
	int			final_x;
	int			final_y;
	double		planeX;
	double		planeY;
	bool		key_fwd;
	bool		key_bwd;
	bool		key_right;
	bool		key_left;
	bool		key_r_right;
	bool		key_r_left;
	int			frames;
	double		acum_time;
} t_data;

void	get_img_buffer(void *img, t_data *info);
double	get_time_in_ms(void);
void	execute_main(t_data *info);
int		pressed_keys(int keycode, void *param);
int		released_keys(int keycode, void *param);
int		apply_movement(void *param);
int		render(t_data *info);
char	*put_pixel_condition(char type, char *p, t_data *info);
void    set_py_in_buffer(t_data *info);
void    rotation_left(t_data *info);
void    rotation_right(t_data *info);
int		close_game(t_data *info);

#endif