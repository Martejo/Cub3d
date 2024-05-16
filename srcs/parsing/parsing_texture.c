#include "../../includes/cub3d.h"

int	search_index_texture(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
			i++;
	if (ft_strncmp(&line[i], "NO", 2) == 0)
		return (NORTH);
	else if (ft_strncmp(&line[i], "SO", 2) == 0)
		return (SOUTH);
	else if (ft_strncmp(&line[i], "WE", 2) == 0)
		return (WEST);
	else if (ft_strncmp(&line[i], "EA", 2) == 0)
		return (EAST);
	else if (ft_strncmp(&line[i], "F", 1) == 0)
		return (F);
	else if (ft_strncmp(&line[i], "C", 1) == 0)
		return (C);
	else
		free_and_exit_error(SYNTAX_LINE);
	return (-1);
}


int index_texture_path(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	i += 2;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		free_and_exit_error(TEXT_PATH);
	return (i);
}

int has_xpm_extension(const char *path)
{
	char *extension; 

	extension = ft_strrchr(path, '.');
	if (ft_strcmp(extension, ".xpm") != 0)
		free_and_exit_error(TEXT_PATH);
	return (0);
}


void extract_texture_path(t_text *texture, const char *line, int index_text)
{
	int		i;
	char	*path;

	i = index_texture_path(line);
	if (i == -1)
		free_and_exit_error(TEXT_PATH);
	has_xpm_extension(&line[i]);
	path = strdup_gc(&line[i], TEXTURE);
	if (!path)
		free_and_exit_error(MALLOC_ERR_MSG);
	if (index_text == NORTH)
		texture->north_texture = path;
	else if (index_text == SOUTH)
		texture->south_texture = path;
	else if (index_text == EAST)
		texture->east_texture = path;
	else if (index_text == WEST)
		texture->west_texture = path;
}

