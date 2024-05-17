/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:59:09 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/15 16:33:43 by gemartel         ###   ########.fr       */
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

ssize_t	read_line(int fd, char **line, char *buffer)
{
	ssize_t	byte_read;
	size_t	line_len;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (-1);
		buffer[byte_read] = '\0';
		*line = extract_line(*line, buffer);
		if (*line == NULL)
			return (-2);
		line_len = check_new_line(*line);
		if ((line_len > 0 || byte_read == 0) && (*line)[0] != '\0')
			return (line_len);
	}
	return (0);
}

// return (-1) == error args
// return (-2) == error malloc line
// return (-3) == error buffer

ssize_t	get_next_line(int fd, char **line)
{
	static t_fd	buffer_memory[MAX_FD];
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE < 1 || MAX_FD < 1 || !line)
		return (-1);
	*line = str_init(*line);
	if (!*line)
		return (-2);
	buffer = init_buffer(fd, buffer_memory);
	if (!buffer)
		return (-3);
	if (update_gnl(buffer, &buffer[check_new_line(buffer)], line) < 0)
		return (-2);
	if (check_new_line(*line) > 0)
		return (gnl_ft_strlen(*line));
	return (read_line(fd, line, buffer));
}