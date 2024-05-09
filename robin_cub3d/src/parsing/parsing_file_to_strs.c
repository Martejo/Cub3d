/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_to_strs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:15:01 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 16:44:50 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_file_size(char *file_name)
{
	char	c;
	int		fd;
	int		len;

	len = 0;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_message_and_exit(1, FD_ARG_ERR_MSG);
	while (read(fd, &c, 1))
		len++;
	close(fd);
	return (len);
}

bool	map_has_empty_line(char *str_file)
{
	int		line;
	char	*map;

	line = 0;
	while (*str_file && line < 6)
	{
		while (*str_file && *str_file == '\n')
			str_file++;
		while (*str_file && *str_file != '\n')
			str_file++;
		line++;
	}
	map = ft_strtrim(str_file, "\n", LOOP);
	if (!map)
		error_message_and_exit(1, MALLOC_ERR_MSG);
	while (*map)
	{
		if (!ft_strncmp(map, "\n\n", 2))
			return (true);
		map++;
	}
	return (false);
}

char	*file_to_string(char *file_name)
{
	char	*file_to_string;
	int		i;
	int		fd;

	file_to_string = NULL;
	file_to_string = mem_alloc((get_file_size(file_name) + 1) * sizeof(char),
			(void**)file_to_string, LOOP);
	if (!file_to_string)
		error_message_and_exit(1, MALLOC_ERR_MSG);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error_message_and_exit(1, FD_ARG_ERR_MSG);
	i = 0;
	while (read(fd, &file_to_string[i], 1))
		i++;
	file_to_string[i] = '\0';
	close(fd);
	if (map_has_empty_line(file_to_string))
		error_message_and_exit(1, INCORECT_MAP_MSG);
	return (file_to_string);
}

void	split_file_string(t_cub3d *prog, char *file_name)
{
	prog->file_to_strs = ft_split(file_to_string(file_name), "\n", MAIN);
	if (!prog->file_to_strs)
		error_message_and_exit(1, MALLOC_ERR_MSG);
}
