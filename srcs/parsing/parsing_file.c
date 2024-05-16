#include "../../includes/cub3d.h"

void	test_and_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (!fd)
		free_and_exit_error(FILE_PATH);
	close(fd);
}

static int	get_size_file(char *file)
{
	int		size;
	int		fd;
	char	c;

	fd = open(file, O_RDONLY);
	if (!fd)
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

	file_data = calloc_gc(get_size_file(file), sizeof(char), TMP);
	if (!file_data)
		free_and_exit_error(MALLOC_ERR_MSG);
	fd = open(file, O_RDONLY);
	if (!fd)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = 0;
	while (read(fd, &file_data[i], 1))
		i++;
	file_data[i] = '\0';
	close(fd);
	return (file_data);
}

char **extract_file(char *file)
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
