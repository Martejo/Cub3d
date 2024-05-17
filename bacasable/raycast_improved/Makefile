NAME = raycast_improved.exe

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

SRCS = main2.c

PATH_MLX = ../../minilibx-linux
PATH_LFT = ../../libft

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	make -C $(PATH_MLX)
	make -C $(PATH_LFT)
	$(CC) $(FLAGS) $(OBJS) -L$(PATH_LFT) -lft -L$(PATH_MLX) -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

%.o: %.c $(INC)
	$(CC) $(FLAGS) -Iincludes/ -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make clean -C $(PATH_MLX)
	@make clean -C $(PATH_LFT)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(PATH_LFT)
# @make fclean -C $(PATH_MLX)

re: fclean all

.PHONY: clean fclean re all