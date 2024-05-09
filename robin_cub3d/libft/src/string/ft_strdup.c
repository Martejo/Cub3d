/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:54:43 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:25:01 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, int garbage)
{
	char	*sdup;
	size_t	len;

	len = ft_strlen(s) + 1;
	if (mem_alloc(len * sizeof(char), (void **)&sdup, garbage))
		return (NULL);
	ft_strlcpy(sdup, s, len);
	return (sdup);
}
