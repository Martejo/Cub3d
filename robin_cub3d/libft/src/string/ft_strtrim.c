/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:34:18 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/20 00:07:37 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char c, char const *set)
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

char	*ft_strtrim(char const *s, char const *set, int garbage)
{
	unsigned int	start;
	size_t			len;
	char			*str;

	if (!s || !set)
		return (NULL);
	start = 0;
	while (is_set(s[start], set) && s[start])
		start++;
	len = ft_strlen(s) - 1;
	if (start == len + 1)
		return (ft_strnew(0, garbage));
	while (is_set(s[len], set))
		len--;
	len = len - start + 1;
	str = ft_substr(s, start, len, garbage);
	if (!str)
		return (NULL);
	return (str);
}
