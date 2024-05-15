#include "../../includes/cub3d.h"

int	test_and_open_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (!fd)
		free_and_exit_error(FILE_PATH);
	return (fd);
}

int	get_size_file(int fd)
{
	int	size;
	int	octets;
	char	*line;

	size = 0;
	octets = 1;
	while (octets > 0)
	{
		octets = get_next_line(fd, &line);
		if (octets > 0)
		{
			size++;
			free(line);
		}
	}
	close (fd);
	if (line)
		free(line);
	if (octets < 0)
		free_and_exit_error(MALLOC_ERR_MSG);
	return (size);
}

char **extract_file(int fd, int size)
{
	char	**data;
	char	*line;
	int		octets;
	int		i;

	octets = 1;
	i = 0;
	data = calloc_gc((size + 1), sizeof(char **), TMP);
	if (!data)
		free_and_exit_error(MALLOC_ERR_MSG);
	while (octets > 0)
	{
		octets = get_next_line(fd, &line);
		if (octets)
		{
			data[i] = strdup_gc(line, TMP);
			free(line);
			if (!data[i])
				free_and_exit_error(MALLOC_ERR_MSG);
			i++;
		}
	}
	close(fd);
	if (line)
		free(line);
	if (octets < 0)
		free_and_exit_error(MALLOC_ERR_MSG);
	return (data);
}

void	parse_file(t_cub3d *data, char **file)
{
	
}

void	parsing_handler(t_cub3d *data, char *file)
{
	int	fd;
	int	size;
	char	**data_file;

	fd = test_and_open_file(file);
	size = get_size_file(fd);
	fd = test_and_open_file(file);
	data_file = extract_file(fd, size);
	parse_file(data, data_file);
	for (int i = 0; data_file[i]; i++)
	 	printf("%s\n", data_file[i]);
	free_and_exit_error("Ok");
}