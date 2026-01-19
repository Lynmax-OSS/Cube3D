Name=cub3D
CC= cc
CFLAGS= -Wall -Wextra -Werror

SRCS= cube3d_main.c parsing/parser.c parsing/validate_map.c \
	  parsing/parse_elements.c parsing/parse_map.c \
	  parsing/parse_colors.c parsing/parser_utils.c\
	  parsing/validate_file.c \

OBJ= $(SRCS:.c=.o)

LIBFT_DIR=./libft

LIBFT=$(LIBFT_DIR)/libft.a

all: $(Name)

$(Name): $(OBJ) libft
		$(CC) $(CFLAGS) -o $(Name) $(OBJ) $(LIBFT) 

libft:
		make -C $(LIBFT_DIR)

clean:
		rm -f $(OBJ)
		make -C $(LIBFT_DIR) clean

fclean: clean
		rm -f $(Name) 
		make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft
