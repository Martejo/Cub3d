/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 12:02:25 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:21:14 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size, int garbage)
{
	void	*ptr;

	if (mem_alloc(nmemb * size, &ptr, garbage))
		return (NULL);
	ft_memset(ptr, 0, nmemb * size);
	return (ptr);
}
