/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:34:51 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/29 15:10:58 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_set(char const *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	len_dest(char const *set, char const *s1)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && is_set(set, s1[start]))
		start++;
	while (end > start && is_set(set, s1[end - 1]))
		end--;
	return (end - start);
}

char	*strtrim_gc(char const *s1, char const *set, int id_gc)
{
	char	*dest;
	size_t	i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	len = len_dest(set, s1);
	if (len <= 0)
		return (strdup_gc("", id_gc));
	dest = (char *)malloc_gc((len + 1) * sizeof(char), id_gc);
	if (!dest)
		return (NULL);
	i = 0;
	while (is_set(set, s1[i]))
		i++;
	ft_strlcpy(dest, &s1[i], len + 1);
	return (dest);
}
