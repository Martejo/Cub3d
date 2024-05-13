/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:32:31 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:32:31 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*byte;
	size_t			i;

	i = 0;
	byte = (unsigned char *)s;
	while (i < n)
	{
		byte[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
