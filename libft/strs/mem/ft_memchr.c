/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:32:08 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:32:08 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*byte;
	size_t			i;

	byte = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (byte[i] == (unsigned char)c)
			return ((void *)&byte[i]);
		i++;
	}
	return (NULL);
}
