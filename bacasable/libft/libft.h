/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:35:30 by hanglade          #+#    #+#             */
/*   Updated: 2024/03/08 15:20:28 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdarg.h>

/**********file**********/
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
/**********gnl**********/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef MAX_FD
#  define MAX_FD 10
# endif

typedef struct s_fd
{
	int		fd;
	char	buffer[BUFFER_SIZE + 1];
}	t_fd;

char	*ft_strdup(const char *str);
size_t	gnl_ft_strlen(char *s);
char	*get_next_line(int fd);
char	*str_init(char *s);
char	*init_buffer(int fd, t_fd *buffer_memory);

/**********memory**********/
void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

/**********nbr**********/
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);
long	ft_atol(const char *s);
int		ft_atoi_base(const char *nptr, char *base, int size_base);

/**********str**********/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t len);
char	*ft_strdup(const char *str);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_toupper(int c);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, const char *src);

/**********char2**********/
char	**char2dup(char **char2);
size_t	char2len(char **char2);
void	free_char2(char ***a_char2);
void	ft_putchar2_endl(char **char2);

/**********Others**********/
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
int		ft_isspace(char c);
int		ft_issign(char c);

/**list**/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstlast(t_list *lst);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstadd_back(t_list **alst, t_list *new);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
int		ft_lstsize(t_list *lst);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/**ft_Printf**/
void	ft_putstr_pf(char *s, size_t *count_char);
void	ft_putchar_pf(char c, size_t *count_char);
void	ft_putnbr_pf(int nbr, size_t *count_char);
void	print_ptr_addr(void *ptr, size_t *count_char);
void	ft_puthexa_upper(unsigned int nbr, size_t *count_char);
void	ft_puthexa_lower(unsigned int nbr, size_t *count_char);
void	ft_putnbr_unsigned(unsigned int nbr, size_t *count_char);
int		ft_printf(const char *str, ...);

/**ft_Printf_fd**/
void	ft_putstr_pf_fd(int fd, char *s, size_t *count_char);
void	ft_putchar_pf_fd(int fd, char c, size_t *count_char);
void	ft_putnbr_pf_fd(int fd, int nbr, size_t *count_char);
void	print_ptr_addr_fd(int fd, void *ptr, size_t *count_char);
void	ft_puthexa_upper_fd(int fd, unsigned int nbr, size_t *count_char);
void	ft_puthexa_lower_fd(int fd, unsigned int nbr, size_t *count_char);
void	ft_putnbr_unsigned_fd(int fd, unsigned int nbr, size_t *count_char);
int		ft_printf_fd(int fd, const char *str, ...);

/**garbage_collector**/

# define GARBAGE_SIZE 10

t_list	**garbage_ptr(int id);
void	*add_to_garbage(void *ptr, int id_gc);
void	*malloc_gc(size_t size, int id_gc);
void	*calloc_gc(size_t nmemb, size_t size, int id_gc);
void	clear_garbage(int id_gc, void (*del)(void*));
void	del_one_garbage(void *ptr_to_free, int id_gc);
t_list	*ft_lstmap_gc(t_list *lst, void *(*f)(void *), void (*del)(void *),
			int id_gc);
t_list	*ft_lstnew_gc(void *content, int id_gc);
void	*realloc_gc(void *ptr, size_t prev_size, size_t new_size, int id_gc);
char	**split_gc(char const *s, char c, int id_gc);
char	*strdup_gc(const char *str, int id_gc);
char	*strjoin_gc(char const *s1, char const *s2, int id_gc);
char	*strtrim_gc(char const *s1, char const *set, int id_gc);
char	*substr_gc(char const *s, unsigned int start, size_t len, int id_gc);
char	*strmapi_gc(char const *s, char (*f)(unsigned int, char), int id_gc);
char	*itoa_gc(int n, int id_gc);
char	*strndup_gc(char *buffer, int len, int id_gc);

#endif
