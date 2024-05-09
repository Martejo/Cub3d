/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:53:42 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/18 16:40:32 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*s;
	size_t	i;

	if (!dest && !src)
		return (NULL);
	s = (char *)dest;
	i = 0;
	while (i < n)
	{
		((char *)s)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
