/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:59:09 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/07 16:17:04 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*extract_line(char *s, char *buffer)
{
	char	*dest;
	size_t	i;
	size_t	j;
	size_t	buff_len;

	i = 0;
	j = 0;
	buff_len = gnl_ft_strlen(buffer);
	dest = (char *)malloc((gnl_ft_strlen(s) + buff_len + 1) * sizeof(char));
	if (!dest)
		return (free(s), NULL);
	while (s[i])
	{
		dest[i] = s[i];
		i++;
	}
	free(s);
	while (j < buff_len && buffer[j - 1] != '\n')
	{
		dest[i] = buffer[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_new_line(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		return (i + 1);
	return (0);
}

int	update_gnl(char *dest, char *src, char **str)
{
	size_t	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	*str = extract_line(*str, dest);
	if (*str == NULL)
		return (-1);
	return (1);
}

char	*read_line(int fd, char *str, char *buffer)
{
	ssize_t	byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			break ;
		buffer[byte_read] = '\0';
		str = extract_line(str, buffer);
		if (str == NULL)
			break ;
		if ((check_new_line(str) > 0 || byte_read == 0) && str[0] != 0)
			return (str);
	}
	buffer[0] = '\0';
	if (str)
		free(str);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_fd	buffer_memory[MAX_FD];
	char		*str;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1 || MAX_FD < 1)
		return (NULL);
	str = NULL;
	str = str_init(str);
	if (!str)
		return (NULL);
	buffer = init_buffer(fd, buffer_memory);
	if (!buffer)
		return (NULL);
	if (update_gnl(buffer, &buffer[check_new_line(buffer)], &str) < 0)
		return (free(str), NULL);
	if (check_new_line(str) > 0)
		return (str);
	return (read_line(fd, str, buffer));
}
