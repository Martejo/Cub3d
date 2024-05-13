NAME = minimap_test

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRCS = main.c

OBJS = $(SRCS:.c=.o)

minimap_test: $(OBJS)
	make -C ../minilibx-linux/
	make -C ../libft
	$(CC) $(FLAGS) $(OBJS) -L../libft -lft -L../minilibx-linux/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

%.o: %.c $(INC)
	$(CC) $(FLAGS) -Iincludes/ -c $< -o $@

clean:
	@rm -rf objs
	@make clean -C libft/

fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: clean fclean re all test