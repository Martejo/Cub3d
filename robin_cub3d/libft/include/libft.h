/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:34:47 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 18:00:00 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdint.h>
# include <fcntl.h>

/*
** List
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

void	ft_lstadd_front(t_list **alst, t_list *new);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstiter(t_list *lst, void (*f)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstadd_here(t_list *alst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *),
			int garbage);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content, int garbage);

/*
** Ctype
*/

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isprint(int c);
char	ft_tolower(char c);
int		ft_toupper(int c);
int		ft_ischarset(int c, char *charset, int (*func_ptr)(int));
char	*ft_itoa(int n, int garbage);

/*
** Stdio
*/

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char const *s, int fd);
void	ft_putendl_fd(char const *s, int fd);
void	ft_putnbr_fd(int n, int fd);

/*
** Stdlib
*/

int		ft_atoi(const char *nptr);
int		ft_abs(int nb);
int		ft_absf(float nb);

/*
** String
*/

char	**ft_split(char const *s, char *sep, int garbage);
char	**ft_split_double(const char *s, char *sep1, char *sep2, int garbage);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len, int garbage);
char	*ft_strjoin(char const *s1, char const *s2, int garbage);
char	*ft_strtrim(char const *s, char const *set, int garbage);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char), int garbage);
char	*ft_strnew(size_t size, int garbage);
char	*ft_strstr(const char *haystack, const char *needle);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strncat(char *dest, const char *src, size_t n);
char	*ft_strmap(char const *s, char (*f)(char), int garbage);
char	*ft_strdup(const char *s, int garbage);
size_t	ft_strlen(const char *s);
size_t	ft_strlento(const char *s, char c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_strclr(char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
void	ft_striter(char *s, void (*f)(char *));
void	ft_strdel(char **as);
void	ft_putnbr_base(int nbr, char *base);
int		ft_strequ(char const *s1, char const *s2);
int		ft_strnequ(char const *s1, char const *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_stradd_quotes(char *str, int garbage);
int8_t	ft_strinsert(char **src, char *to_insert, int start, int stop);
char	**ft_split_noquote(const char *s, char *sep, int garbage);
int		ft_strarr_size(char **arr);
char	*ft_sort_strarr(char *arg, int garbage);

/*
** Memory
*/

void	*ft_memset(void *s, int c, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
void	ft_memdel(void **ap);
void	*ft_memalloc(size_t size, int garbage);
void	*ft_calloc(size_t nmemb, size_t size, int garbage);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size, int garbage);

/*
** Get_next_line
*/

char	*get_next_line(int fd);
char	*ft_join_gnl(char *s1, char *s2);
int		no_newline_in(char *s);

/*
**	Garbage collector
*/

t_list	**garbage(int id);
void	*mem_alloc(unsigned long size, void **ptr, int id);
void	*garbage_addptr(void *ptr, int id);
void	del_garbage(int id);
void	mem_remove(void *ptr_to_free, int id);
t_list	*garbage_lstnew(void *content);

#endif
