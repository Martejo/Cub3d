/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_gc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:33:01 by hanglade          #+#    #+#             */
/*   Updated: 2024/03/08 15:22:43 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	free_subs(char	**strs, size_t nb_subs, int id_gc)
{
	size_t	i;

	i = 0;
	while (i < nb_subs)
	{
		del_one_garbage(strs, id_gc);
		strs[i] = NULL;
		i++;
	}
}

static int	count_subchain(char *s, char c)
{
	unsigned int	count;
	size_t			i;
	int				is_separator;

	is_separator = 1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && is_separator)
			count++;
		is_separator = (c == s[i]);
		i++;
	}
	return (count);
}

static char	*create_subchain(char *s, char c, int id_gc)
{
	size_t	i;
	size_t	len;
	char	*str;

	i = 0;
	len = 0;
	str = NULL;
	while (s[len] && s[len] != c)
		len++;
	str = (char *)malloc_gc((len + 1) * sizeof(char), id_gc);
	if (!str)
		return (NULL);
	while (s[i] && s[i] != c)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static int	create_strs(char const *s, char **strs, char c, int id_gc)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != '\0')
		{
			strs[j] = create_subchain((char *)&s[i], c, id_gc);
			if (strs[j] == NULL)
			{
				free_subs(strs, j, id_gc);
				return (0);
			}
			j++;
		}
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	strs[j] = NULL;
	return (1);
}

char	**split_gc(char const *s, char c, int id_gc)
{
	char	**strs;
	size_t	len_subchain;

	if (s == NULL)
		return (NULL);
	len_subchain = count_subchain((char *)s, c);
	strs = (char **)malloc_gc((len_subchain + 1) * sizeof(char *), id_gc);
	if (!strs)
		return (NULL);
	if (!create_strs(s, strs, c, id_gc))
		return (del_one_garbage(strs, id_gc), NULL);
	return (strs);
}
