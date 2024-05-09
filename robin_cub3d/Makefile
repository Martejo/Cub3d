# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 14:42:18 by cberganz          #+#    #+#              #
#    Updated: 2022/06/06 15:02:13 by rbicanic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3D
NAME_BONUS		= cub3D_bonus

INCLUDE			= include/

HEADER			= ${INCLUDE}cub3d.h

CC				= clang

CFLAGS			= -Wall -Wextra -Werror -g

FLAG			= 0

SRC_NAME		=	main.c			\
					minimap.c		\
					raycast.c		\
					mouse.c			\
					game.c			\
					initialize.c	\
					utils.c			\
					parsing/parsing_file_to_strs.c		\
					parsing/parsing_file_get_textures.c	\
					parsing/check_path.c				\
					parsing/check_map_error.c			\
					parsing/check_instructions_error.c	\
					parsing/parsing_images.c			\
					parsing/parsing_init_elements.c		\
					parsing/global_parsing.c			\
					utils/utils_exit.c					\
					utils/utils_str_to_int.c			\
					torch_animation.c					\
					raycast_init_data.c					\
					hitbox.c							\
					key_hooks.c							\
					player_movements.c					\
					parsing/parsing_get_map.c	


SRC_DIR			= src/
SRC				= ${addprefix ${SRC_DIR}, ${SRC_NAME}}

OBJ_DIR			= objs/
OBJ_DIRS		= ${sort ${dir ${OBJ}}}
OBJ_NAME		= ${SRC_NAME:.c=.o}
OBJ				= ${addprefix ${OBJ_DIR}, ${OBJ_NAME}}

all: ${NAME}

$(NAME): $(OBJ)
	@make -sC ./libft/
	@make -sC ./mlx-linux/
	$(CC) $(CFLAGS) -D BONUS_FLAG=0 -L./libft ${OBJ} -lft -Lmlx-linux -lmlx_Linux -L/usr/lib -Ilibmlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus: bonus_flag $(OBJ)
	@make -sC ./libft/
	@make -sC ./mlx-linux/
	$(CC) $(CFLAGS) -D BONUS_FLAG=1 -L./libft ${OBJ} -lft -Lmlx-linux -lmlx_Linux -L/usr/lib -Ilibmlx_linux -lXext -lX11 -lm -lz -o $(NAME)

bonus_flag: 
	$(eval FLAG=1)

${OBJ_DIRS}:
	mkdir -p $@

${OBJ}: | ${OBJ_DIRS}

${OBJ_DIR}%.o: ${SRC_DIR}%.c ${HEADER}
	${CC} ${CFLAGS} -D BONUS_FLAG=$(FLAG) -I${INCLUDE} -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	@make clean -sC ./libft/
	@make clean -sC ./mlx-linux/
	rm -rf ${OBJ_DIR}

fclean: clean
	@make fclean -sC ./libft/
	rm -f ${NAME}
	rm -f ${NAME_BONUS}

re: fclean all

.PHONY : all clean fclean re
