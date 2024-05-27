# NAME = cub3d

# CC = gcc

# FLAGS = -Wall -Wextra -Werror -g3

# SRCS = 	main.c\

# INC = cub3d.h

# OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

# $(NAME) : $(OBJS)
# 	make -C libft/
# 	make -C minilibx-linux/
# 	$(CC) $(FLAGS) $(OBJS) -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

# objs/%.o : %.c $(INC)
# 	mkdir -p $(dir $@)
# 	$(CC) $(FLAGS) -I includes/ -c $< -o $@

# all : $(NAME)

# clean :
# 	rm -rf objs/
# 	@make clean -C libft/ 

# fclean : clean
# 	rm -f $(NAME)
# 	@make fclean -C libft

# re : fclean all

# test : re
# 	./cub3d

# .PHONY : clean fclean re all test

NAME = cub3d

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

INC = /includes/cub3d.h
# attention les modifs sur le .h et sur le Makefile ne recompilent pas !
OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) 
	make -C libft/
	make -C minilibx-linux/
	$(CC) $(FLAGS) $(OBJS) -I $(INC) -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

%.o: %.c $(INC)
	$(CC) $(FLAGS) -Iincludes/ -c $< -o $@

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

test: re
	./cub3d

# bacasable1 : re
# 	$(CC) $(FLAGS) $(OBJS) -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o bs1 -lX11 -lXext -lm -lmlx
# 	@make fclean


.PHONY: clean fclean re all test