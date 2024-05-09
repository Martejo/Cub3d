/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:28:40 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:21:54 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size, int garbage)
{
	void	*alloc;

	if (size == 0)
		return (NULL);
	if (mem_alloc(size * sizeof(char), &alloc, garbage))
		return (NULL);
	ft_bzero(alloc, size);
	return (alloc);
}
