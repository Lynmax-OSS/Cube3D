/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhor <jhor@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:32:25 by jhor              #+#    #+#             */
/*   Updated: 2026/05/04 16:22:19 by jhor             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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

# define ESCAPE XK_Escape
# define FORWARD XK_w
# define BACKWARD XK_s
# define LEFT XK_a
# define RIGHT XK_d
# define A_LEFT XK_Left
# define A_RIGHT XK_Right
# define WALL_COLL 0.2

typedef struct s_img
{
	int		img_w;
	int		img_h;
	int		bpp;
	int		line_len;
	int		endian;
	char	*data;
}	t_img;

typedef struct s_text
{
	int		bpp;
	int		line_len;
	int		endian;
	char	*data;
	void	*img;
	int		img_width;
	int		img_height;
}	t_text;

typedef struct s_floor
{
	float	raydirx0;
	float	raydiry0;
	float	raydirx1;
	float	raydiry1;
	float	floorx;
	float	floory;
	float	rowdistance;
	float	floorstepx;
	float	floorstepy;
}	t_floor;

typedef struct s_ray
{
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	int			stepx;
	int			stepy;
	int			side;
	double		perpwalldist;
}	t_ray;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win;
	void		*img;
	double		oldtime;
	double		movespeed;
	double		rotspeed;
	t_img		*image;
	t_scene		*map;
	int			tile;
	int			final_x;
	int			final_y;
	bool		key_fwd;
	bool		key_bwd;
	bool		key_right;
	bool		key_left;
	bool		key_r_right;
	bool		key_r_left;
	int			frames;
	double		acum_time;
	double		planex;
	double		planey;
	t_ray		*ray;
	t_text		texture[4];
	t_text		*chosen_text;
	int			texx;
	double		step;
	double		texpos;
	int			texy;
	t_floor		*horizon;
}	t_data;

void	init_info(t_scene *scene, t_data *info);
void	set_ray_variables(t_ray *ray);
void	set_key_bool(t_data *info);
void	set_plane(t_player *player, t_data *info);
void	set_py_direction(t_player *player);
void	load_textures(t_text *texture, t_data *info);
void	get_img_buffer(void *img, t_data *info);
double	get_time_in_ms(void);
void	execute_main(t_data *info);
int		pressed_keys(int keycode, void *param);
int		released_keys(int keycode, void *param);
int		apply_movement(void *param);
int		render(t_data *info);
void	minimap_render(t_data *info);
char	*put_pixel_condition(char type, char *p, t_data *info);
void	draw_ray_in_minimap(t_ray *ray, t_data *info);
void	set_py_in_minimap(t_data *info);
void	compute_buffer(double *buffer, double step);
void	move_forward(char **map, double *x, double *y, t_data *info);
void	move_backward(char **map, double *x, double *y, t_data *info);
void	ne_strafe_right(char **map, double *x, double *y, t_data *info);
void	ne_strafe_left(char **map, double *x, double *y, t_data *info);
void	sw_strafe_right(char **map, double *x, double *y, t_data *info);
void	sw_strafe_left(char **map, double *x, double *y, t_data *info);
void	ne_rotation_left(t_data *info);
void	ne_rotation_right(t_data *info);
void	sw_rotation_left(t_data *info);
void	sw_rotation_right(t_data *info);
int		close_game(t_data *info);
void	raydirection(t_ray *ray, t_data *info);
void	raydistance(t_ray *ray, t_data *info);
void	run_dda(int mapx, int mapy, t_ray *ray, t_data *info);
void	draw_line_stripe(int x, double perpwalldist, t_ray *ray, t_data *info);
void	assign_colour(int *colour, t_text *text, t_data *info);
void	calculate_step(int drawstart, int lineheight, t_data *info);
void	find_text(double pwd, t_ray *ray, t_data *info);
void	put_pixel(int x, int y, int colour, t_data *info);
void	floor_cast(t_floor *horizon, t_data *info);
void	free_scene(t_data *info);
void	destroy_textures(t_data *info);

#endif