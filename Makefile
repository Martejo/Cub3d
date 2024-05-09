NAME = cub3d

CC = gcc

FLAGS = -Wall -Wextra -Werror -g3

SRCS = 	srcs/main.c\

INC = cub3d.h

OBJS = $(patsubst srcs/%.c,objs/%.o,$(SRCS))

$(NAME) : $(OBJS)
	make -C libft/
	make -C minilibx-linux/
	$(CC) $(FLAGS) $(OBJS) -Llibft -lft -Lminilibx-linux/ -lmlx_Linux -o $(NAME) -lX11 -lXext -lm -lmlx

objs/%.o : srcs/%.c $(INC)
	mkdir -p $(dir $@)
	$(CC) $(FLAGS) -I includes/ -c $< -o $@

all : $(NAME)

clean :
	rm -rf objs/
	@make clean -C libft/ 

fclean : clean
	rm -f $(NAME)
	@make fclean -C libft

re : fclean all

test : re
	./cub3d

.PHONY : clean fclean re all test