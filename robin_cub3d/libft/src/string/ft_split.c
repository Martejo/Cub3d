/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:48:27 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:24:06 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_rows(const char *s, char *sep)
{
	int	rows;

	rows = 0;
	while (*s)
	{
		while (ft_strnequ(&(*s), sep, ft_strlen(sep)))
			s += ft_strlen(sep);
		if (*s && !ft_strnequ(&(*s), sep, ft_strlen(sep)))
			rows++;
		while (*s && !ft_strnequ(&(*s), sep, ft_strlen(sep)))
			s += ft_strlen(sep);
	}
	return (rows);
}

static void	*mr_propre(char **str_arr, int garbage)
{
	int	i;

	i = -1;
	while (str_arr[++i])
		mem_remove(str_arr[i], garbage);
	mem_remove(str_arr, garbage);
	return (NULL);
}

static int	ft_wordlen(const char *s, char *sep)
{
	char	*str_end;

	str_end = ft_strstr(s, sep);
	if (!str_end)
		return (ft_strlen(s));
	else
		return (str_end - s);
}

char	**ft_split(const char *s, char *sep, int garbage)
{
	int		i;
	int		n;
	char	**str_arr;

	if (!s || !sep)
		return (NULL);
	str_arr = mem_alloc(sizeof(char *) * (ft_rows(s, sep) + 1), NULL, garbage);
	if (!str_arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_strnequ(&(*s), sep, ft_strlen(sep)))
			s += ft_strlen(sep);
		if (*s && !ft_strnequ(&(*s), sep, ft_strlen(sep)))
		{
			n = ft_wordlen(s, sep);
			str_arr[i++] = ft_substr(s, 0, n, garbage);
			if (!str_arr[i - 1])
				return (mr_propre(str_arr, garbage));
			s += n;
		}
	}
	str_arr[i] = NULL;
	return (str_arr);
}
