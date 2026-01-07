#ifndef PARSER_H
# define PARSER_H

typedef	struct	s_texture
{
	char	*path;
	int		is_set;
}	t_texture;

typedef struct	s_color
{
	int	value;
	int	is_set;
}	t_color;

typedef struct	s_player
{
	double	x;
	double	y;
	char	dir;
	int		is_set;
}	t_player;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
}	t_map;

typedef struct s_scene
{
	t_texture	no;
	t_texture	so;
	t_texture	we;
	t_texture	ea;

	t_color		floor;
	t_color		ceiling;

	t_player	player;
	t_map		map;
}	t_scene;


int extension_check(char *filepath);

#endif