/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:58:10 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/17 16:11:48 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	test_and_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (!fd)
		free_and_exit_error(FILE_PATH);
	close(fd);
}

//A voir si rajouter gestion d'erreur pour read
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
	char	c;
	int		fd;
	int		i;

	int	size = 0;
	
	size = get_size_file(file);
	printf("size file = %d\n", size);
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

char	**extract_file(char *file)
{
	char	*file_str;
	char	**split_file;

	file_str = file_to_str(file);
	split_file = split_gc(file_str, '\n', TMP);
	if (!split_file)
		free_and_exit_error(MALLOC_ERR_MSG);
	del_one_garbage(file_str, TMP);
	return (split_file);
}
