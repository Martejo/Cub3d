NAME = cub3d

all: force $(NAME)

NAME_LARGE = cub3d_large

NAME_SLOW = cub3d_slow

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS =	srcs/main.c \
		srcs/init_struct/init_struct.c \
		srcs/init_struct/init_mlx.c \
		srcs/init_struct/init_sprite.c \
		srcs/errors/manage_errors.c \
		srcs/parsing/parsing_handler.c \
		srcs/parsing/colors_parsing.c \
		srcs/parsing/file_parsing.c \
		srcs/parsing/map_parsing.c \
		srcs/parsing/map_utils_parsing.c \
		srcs/parsing/texture_parsing.c \
		\
		srcs/game_loop/controller/key_management.c \
		\
		srcs/game_loop/frame/print_frame.c \
		\
		srcs/game_loop/player/player_init.c \
		srcs/game_loop/player/player_modifs.c \
		srcs/game_loop/player/player_utils.c \
		\
		srcs/game_loop/ray_casting/dda_wall_config.c \
		srcs/game_loop/ray_casting/dda_ray_config.c \
		\
		srcs/game_loop/game_loop.c \
		\
		srcs/debug/print_debug.c \

INC = includes/cub3d.h 

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -I ./includes -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

%.o: %.c $(INC) Makefile
	$(CC) $(FLAGS) -Iincludes/ -c $< -o $@


clean:
	@$(RM) $(OBJS)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME) $(NAME_LARGE) $(NAME_SLOW)
	@make fclean -C libft

re: fclean all


large : $(NAME_LARGE)

force : 
	make -C libft/
	make -C minilibx-linux/

show : all large
	@echo "Show little map with slow moves and bricks textures\n"
	@./cub3d ./maps/basic_bricks.cub
	@echo "\nShow big map with fast moves and rubikscube textures\n"
	@./cub3d_large ./maps/rubiksE.cub
	@echo "\nShow big map with fast moves and bank textures\n"
	@./cub3d_large ./maps/bank.cub
	@make fclean

$(NAME_LARGE) : $(OBJS)
	make -C libft/
	make -C minilibx-linux/
	$(CC) -D PLANE_FOV=1.2 -D SCREEN_WIDTH=1400 -D SCREEN_HEIGHT=600 -D PLAYER_STEP_SIZE=0.08 -D PLAYER_ROT_SPEED=0.036 $(FLAGS) $(SRCS) -I ./includes -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o $(NAME_LARGE) -lX11 -lXext -lm -lmlx

.PHONY: clean fclean re all large show