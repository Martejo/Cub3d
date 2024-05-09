SRCS	=	\
			file/ft_putchar_fd.c \
			file/ft_putendl_fd.c \
			file/ft_putnbr_fd.c \
			file/ft_putstr_fd.c \
			\
			strs/char2dup.c \
			strs/char2len.c \
			strs/free_char2.c \
			strs/ft_putchar2_endl.c\
			\
			lst/ft_lstadd_back.c\
			lst/ft_lstadd_front.c\
			lst/ft_lstclear.c\
			lst/ft_lstdelone.c\
			lst/ft_lstiter.c\
			lst/ft_lstlast.c\
			lst/ft_lstmap.c\
			lst/ft_lstnew.c\
			lst/ft_lstsize.c\
			\
			mem/ft_memset.c\
			mem/ft_bzero.c\
			mem/ft_calloc.c\
			mem/ft_memchr.c\
			mem/ft_memcmp.c\
			mem/ft_memcpy.c\
			mem/ft_memmove.c\
			\
			nbr/ft_atoi.c\
			nbr/ft_atol.c\
			nbr/ft_atoi_base.c\
			nbr/ft_itoa.c\
			\
			others/ft_isprint.c\
			others/ft_isspace.c\
			others/ft_isdigit.c\
			others/ft_isalnum.c\
			others/ft_isalpha.c\
			others/ft_isascii.c\
			others/ft_issign.c\
			\
			str/ft_strjoin.c \
			str/ft_strdup.c\
			str/ft_tolower.c \
			str/ft_strtrim.c \
			str/ft_strlcat.c \
			str/ft_substr.c \
			str/ft_strlcpy.c \
			str/ft_strlen.c\
			str/ft_toupper.c \
			str/ft_strmapi.c \
			str/ft_split.c \
			str/ft_strncmp.c \
			str/ft_strchr.c\
			str/ft_strnstr.c \
			str/ft_strrchr.c \
			str/ft_striteri.c \
			str/ft_strcmp.c \
			str/ft_strcat.c\
			\
			gnl/get_next_line.c\
			gnl/get_next_line_utils.c\
			\
			printf/ft_printf.c\
			printf/ft_putchar_pf.c\
			printf/ft_puthexa.c\
			printf/ft_putnbr_pf.c\
			printf/ft_putptr_pf.c\
			printf/ft_putstr_pf.c\
			\
			printf_fd/ft_printf_fd.c\
			printf_fd/ft_putchar_pf_fd.c\
			printf_fd/ft_puthexa_fd.c\
			printf_fd/ft_putnbr_pf_fd.c\
			printf_fd/ft_putptr_pf_fd.c\
			printf_fd/ft_putstr_pf_fd.c\
			\
			gc/add_to_garbage.c \
			gc/calloc_gc.c \
			gc/clear_garbage.c \
			gc/del_one_garbage.c \
			gc/ft_lstmap_gc.c \
			gc/ft_lstnew_gc.c \
			gc/garbage_ptr.c \
			gc/malloc_gc.c \
			gc/realloc_gc.c \
			gc/split_gc.c \
			gc/strdup_gc.c \
			gc/strjoin_gc.c \
			gc/strmapi_gc.c \
			gc/strtrim_gc.c \
			gc/substr_gc.c \
			gc/itoa_gc.c \
			gc/strndup_gc.c \

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -rf


%.o:	%.c libft.h 
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
	ar rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		${RM} */*.o

fclean:		clean
		${RM} ${NAME}

re:		fclean all
