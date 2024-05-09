/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:33:14 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:29:50 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char), int garbage)
{
	char			*nstr;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	nstr = ft_strnew(ft_strlen(s), garbage);
	if (!nstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		nstr[i] = f(i, s[i]);
		i++;
	}
	return (nstr);
}
