Name=cub3D
CC= cc
CFLAGS= -Wall -Wextra -Werror -g3
RM = rm -rf

LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a

MLX_DIR = minilibx-linux/
MLX = $(MLX_DIR)libmlx.a
MLX_LIB = -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz

SRCS= cube3d_main.c init/init1.c init/init2.c init/load_textures.c \
	  parsing/parser.c parsing/validate_map.c \
	  parsing/parse_elements.c parsing/parse_map.c parsing/store_map.c\
	  parsing/parse_colors.c parsing/parser_utils.c\
	  parsing/validate_file.c \
	  execution/execute_main.c \
	  execution/minimap/minimap_player_render.c execution/minimap/minimap_ray_render.c \
	  execution/minimap/minimap_render.c \
	  execution/frames/fps.c \
	  execution/movements/forward_backward.c execution/movements/initial.c \
	  execution/movements/strafe.c execution/movements/rotation.c \
	  execution/movements/validate_keys.c \
	  execution/raycasting/raydirection.c execution/raycasting/raydistance.c \
	  execution/raycasting/dda.c execution/raycasting/draw_line_stripe.c \
	  execution/raycasting/pick_texture.c \
	  execution/floor_ceiling/horizontal_cast.c \

OBJ= $(SRCS:.c=.o)

$(Name): $(OBJ) $(LIBFT) $(MLX)
		@$(CC) $(CFLAGS) -I. -Ilibft -Iminilibx-linux $(OBJ) $(LIBFT) $(MLX) $(MLX_LIB) -o $@

all: $(Name)

%.o : %.c
		@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
		make -C $(LIBFT_DIR)

$(MLX):
		make -C $(MLX_DIR)

clean:
		@$(RM) $(OBJ)
		make clean -C $(LIBFT_DIR) clean
		make clean -C $(MLX_DIR) clean

fclean: clean
		@$(RM) $(Name)
		make fclean -C $(LIBFT_DIR)

re: fclean $(Name)

.PHONY: all clean fclean re libft
