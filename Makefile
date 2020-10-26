NAME = cub3d

CC = clang

SRC = cub3d.c srcs/init_game.c srcs/raycasting.c srcs/key_manager.c srcs/draw_sprite.c \
		srcs/parse_map.c srcs/utils.c srcs/draw_wall.c srcs/split_sep.c srcs/screenshot.c \
		srcs/raycasting_2.c srcs/parse_header_map.c srcs/parse_count.c srcs/parse_colors.c \
		srcs/set_map.c srcs/check_map.c srcs/check_map_utils.c srcs/key_manager_utils.c \
		srcs/errors_utils.c srcs/exit_game.c

CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		make -j -C minilibx_opengl
		make -j -C libft
		mv minilibx_opengl/libmlx.a .
		mv libft/libft.a .
		CC $(CFLAGS) -I./include -L. -lmlx -framework OpenGL -framework Appkit $(OBJ) ./libft.a -o $(NAME)

debug: CFLAGS += -g3
debug: re

sanitize: CFLAGS += -fsanitize=address -g3
sanitize: debug

clean:
		make -C minilibx_opengl clean
		make -C libft clean
		rm -rf $(OBJ) libft.a libmlx.a

fclean: clean
		make -C minilibx_opengl clean
		make -C libft fclean
		rm -rf $(NAME)
		rm -rf screenshot.bmp

re : fclean all