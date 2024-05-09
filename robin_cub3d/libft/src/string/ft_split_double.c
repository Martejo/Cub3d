/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:48:27 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/24 16:41:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	quote_len(char *sub_input, char quote)
{
	int	i;

	i = 1;
	while (sub_input[i] && sub_input[i] != quote)
		i++;
	return (i);
}

static int	ft_rows(const char *s, char *sep1, char *sep2)
{
	int	rows;

	rows = 0;
	while (*s)
	{
		while (ft_strnequ(&(*s), sep1, 2) || ft_strnequ(&(*s), sep2, 2))
			s += 2;
		if (*s && !ft_strnequ(&(*s), sep1, 2) && !ft_strnequ(&(*s), sep2, 2))
			rows++;
		while (*s && !ft_strnequ(&(*s), sep1, 2) && !ft_strnequ(&(*s), sep2, 2))
		{
			if (*s == '"')
				s += quote_len((char *)s, '"');
			else if (*s == '\'')
				s += quote_len((char *)s, '\'');
			s++;
		}
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

static int	ft_wordlen(const char *s, char *sep1, char *sep2)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			i += quote_len(&((char *)s)[i], '"') + 1;
		else if (s[i] == '\'')
			i += quote_len(&((char *)s)[i], '\'') + 1;
		else if (!ft_strncmp(&s[i], sep1, ft_strlen(sep1)))
			return (i);
		else if (!ft_strncmp(&s[i], sep2, ft_strlen(sep2)))
			return (i);
		else
			i++;
	}
	return (i);
}

char	**ft_split_double(const char *s, char *sep1, char *sep2, int garbage)
{
	int		i;
	int		n;
	char	**str_arr;

	if (!s || !sep1 || !sep2)
		return (NULL);
	if (mem_alloc(sizeof(char *) * (ft_rows(s, sep1, sep2) + 1),
			(void **)&str_arr, garbage))
		return (NULL);
	i = 0;
	while (*s)
	{
		while (ft_strnequ(&(*s), sep1, 2) || ft_strnequ(&(*s), sep2, 2))
			s += 2;
		if (*s && !ft_strnequ(&(*s), sep1, 2) && !ft_strnequ(&(*s), sep2, 2))
		{
			n = ft_wordlen(s, sep1, sep2);
			str_arr[i++] = ft_substr(s, 0, n, garbage);
			if (!str_arr[i - 1])
				return (mr_propre(str_arr, garbage));
			s += n;
		}
	}
	str_arr[i] = NULL;
	return (str_arr);
}
