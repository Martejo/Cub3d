/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:33:11 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:33:11 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*current;

	current = s;
	while (*current != '\0')
	{
		if (*current == (unsigned char)c)
			return ((char *)current);
		current++;
	}
	if (*current == (unsigned char)c)
		return ((char *)current);
	return (NULL);
}
