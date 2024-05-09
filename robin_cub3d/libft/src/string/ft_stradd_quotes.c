/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stradd_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 19:06:32 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:33:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stradd_quotes(char *str, int garbage)
{
	char	*nstr;
	int		i;

	if (!str || str[0] == '\0')
		return (str);
	if (mem_alloc(ft_strlen(str) + 3, (void **)&nstr, garbage))
		return (NULL);
	nstr[0] = '"';
	i = 1;
	while (str[i - 1])
	{
		nstr[i] = str[i - 1];
		i++;
	}
	nstr[i] = '"';
	nstr[i + 1] = '\0';
	mem_remove(str, garbage);
	return (nstr);
}
