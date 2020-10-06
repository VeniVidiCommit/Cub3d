NAME = cub3d

SRC = cub3d.c init_game.c raycasting.c key_manager.c draw_sprite.c \
		parse_map.c

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -j -C minilibx_opengl
		make -j -C libft
		mv minilibx_opengl/libmlx.a .
		mv libft/libft.a .
		gcc $(CFLAGS) -c $(SRC)
		gcc $(CFLAGS) -L. -lmlx -framework OpenGL -framework Appkit $(OBJ) ./libft.a -o $(NAME)

debug: CFLAGS += -g3
debug: re

sanitize: CFLAGS += -fsanitize=address -g3
sanitize: debug

clean:
		make -C minilibx_opengl clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx_opengl clean
		rm -rf $(NAME)

re : fclean all