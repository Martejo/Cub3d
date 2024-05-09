/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strndup_gc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 10:19:35 by hanglade          #+#    #+#             */
/*   Updated: 2024/03/08 15:23:19 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*strndup_gc(char *buffer, int len, int id_gc)
{
	char	*new;
	int		i;

	i = 0;
	while (buffer[i] && i < len)
		i++;
	new = malloc_gc((i + 1) * sizeof(char), id_gc);
	if (!new)
		NULL;
	i = 0;
	while (buffer[i] && i < len)
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
