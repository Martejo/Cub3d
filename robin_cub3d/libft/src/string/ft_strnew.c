/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:33:56 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:27:45 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size, int garbage)
{
	char	*nstr;

	if (mem_alloc(size + 1 * sizeof(char), (void **)&nstr, garbage))
		return (NULL);
	ft_memset(nstr, '\0', size + 1);
	return (nstr);
}
