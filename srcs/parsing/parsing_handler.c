#include "../../includes/cub3d.h"

//// Rajouter fonction struct player avec postion et caractere a extraire
///	extract_data_player direction + pos

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	parse_texture_color(t_cub3d *data, char **file)
{
	int	i;
	int	index_text;
	int	line_nbr;

	i = 0;
	line_nbr = 0;
	while (file[i] && line_nbr < 6)
	{
		if (is_empty_line(file[i]))
			i++;
		else
		{
			index_text = search_index_texture(file[i]);
			if (index_text == F || index_text == C)
				extract_color(&data->text, file[i], index_text);
			else
				extract_texture_path(&data->text, file[i], index_text);
			line_nbr++;
		}
		i++;
	}
	if (file[i] == NULL || line_nbr != 6) 
		free_and_exit_error(SYNTAX_LINE);
	return (i);
}

void	parse_file(t_cub3d *data, char **file)
{
	int	i;

	i = parse_texture_color(data, file);
	data->map.grid = extract_map(&file[i]);

}

void	parsing_handler(t_cub3d *data, char *file)
{
	
	char	**data_file;

	data_file = extract_file(file);
	if (!data_file)
		free_and_exit_error(MALLOC_ERR_MSG);
	parse_file(data, data_file);
	print_texture_debug(&data->text);
	print_map_debug(&data->map);
	free_and_exit_error("Ok");
}