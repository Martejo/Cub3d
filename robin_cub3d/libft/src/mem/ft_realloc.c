/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:41:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/24 16:45:29 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t prev_size, size_t new_size, int garbage)
{
	void	*new;
	size_t	size;

	if (!ptr)
		return (NULL);
	if (mem_alloc(new_size, &new, garbage))
	{
		mem_remove(ptr, garbage);
		return (NULL);
	}
	if (prev_size < new_size)
		size = prev_size;
	else
		size = new_size;
	ft_memcpy(new, ptr, size);
	mem_remove(ptr, garbage);
	return (new);
}
