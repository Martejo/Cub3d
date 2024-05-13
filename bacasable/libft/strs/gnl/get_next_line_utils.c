/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:40:26 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/07 15:13:25 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	gnl_ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i + 1);
	return (i);
}

char	*str_init(char *s)
{
	s = (char *)malloc(1 * sizeof(char));
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*init_buffer(int fd, t_fd *buffer_memory)
{
	size_t	i;

	i = 0;
	fd++;
	while (i < MAX_FD && buffer_memory[i].fd != fd)
	{
		if (buffer_memory[i].fd == 0)
		{
			buffer_memory[i].fd = fd;
			return (buffer_memory[i].buffer);
		}
		i++;
	}
	if (buffer_memory[i].fd == fd)
		return (buffer_memory[i].buffer);
	return (NULL);
}
