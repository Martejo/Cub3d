/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:32:26 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:32:26 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*cast_dest;
	unsigned char	*cast_src;

	cast_dest = (unsigned char *) dest;
	cast_src = (unsigned char *) src;
	if (dest == 0 && src == 0 && n > 0)
		return (0);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			cast_dest[n - 1] = cast_src[n - 1];
			n--;
		}
	}
	return (dest);
}
