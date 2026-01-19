#ifndef PARSER_H
# define PARSER_H
#include "../libft/libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

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


void		parse_file(char *path, t_scene *scene);
void		parse_color(char *line, t_scene *scene);
void		parse_texture(char *line, t_scene *scene);
void		parse_map(int fd, char *first, t_scene *scene);
char		*skip_spaces(char *s);
void		error_exit(char *msg);
int			is_empty_line(char *line);
int			is_map_line(char *line);
void		free_split(char **s);
void		validate_scene(t_scene *scene);
void		validate_map(t_scene *scene);
void		print_map(t_scene *s);

#endif