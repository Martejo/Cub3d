/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:59 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/30 14:36:55 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	test_and_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit_error(FILE_PATH);
	close(fd);
}

static int	get_size_file(char *file)
{
	int		size;
	int		fd;
	char	c;

	size = 0;
	c = '0';
	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit_error(FILE_PATH);
	while (read(fd, &c, 1))
		size++;
	close(fd);
	return (size);
}

static char	*file_to_str(char *file)
{
	char	*file_data;
	int		fd;
	int		i;
	int		size;

	size = get_size_file(file);
	file_data = (char *) calloc_gc(size + 1, sizeof(char), TMP);
	if (!file_data)
		free_and_exit_error(MALLOC_ERR_MSG);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = 0;
	while (read(fd, &file_data[i], 1))
		i++;
	file_data[i] = '\0';
	close(fd);
	return (file_data);
}

bool	map_has_empty_line(char *str_file)
{
	char	*map;

	map = ft_strtrim(&str_file[find_start_map(str_file)], "\n");
	if (!map)
		free_and_exit_error(MALLOC_ERR_MSG);
	add_to_garbage(map, TMP);
	while (*map)
	{
		if (!ft_strncmp(map, "\n\n", 2))
			return (true);
		map++;
	}
	del_one_garbage(map, TMP);
	return (false);
}

char	**extract_file(char *file)
{
	char	*file_str;
	char	**split_file;

	file_str = file_to_str(file);
	if (map_has_empty_line(file_str))
		free_and_exit_error(MAP_LINE_BREAK);
	split_file = split_gc(file_str, '\n', TMP);
	if (!split_file)
		free_and_exit_error(MALLOC_ERR_MSG);
	del_one_garbage(file_str, TMP);
	return (split_file);
}
