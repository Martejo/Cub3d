/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:33:06 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/11 02:06:33 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char), int garbage)
{
	char			*nstr;
	unsigned int	i;

	if (!s)
		return (NULL);
	nstr = ft_strnew(ft_strlen(s), garbage);
	if (!nstr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		nstr[i] = f(s[i]);
		i++;
	}
	return (nstr);
}
