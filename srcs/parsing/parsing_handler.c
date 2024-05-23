/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:56:20 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/23 13:26:37 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	parse_texture_and_color_lines(t_cub3d *data, char **file)
{
	int	i;
	int	index_text;
	int	line_nbr;

	i = -1;
	line_nbr = 0;
	while (file[++i] && line_nbr < 6)
	{
		if (is_empty_line(file[i]))
			i++;
		else
		{
			index_text = get_texture_index_from_line(file[i]);
			if (index_text == F || index_text == C)
				extract_color(&data->colors, file[i], index_text);
			else
				extract_texture_path(&data->text_path, file[i], index_text);
			line_nbr++;
		}
	}
	if (file[i] == NULL || line_nbr != 6)
		free_and_exit_error(SYNTAX_LINE);
	return (i);
}

void	process_config_and_map(t_cub3d *data, char *file)
{
	int		i;
	char	**data_file;

	data_file = extract_file(file);
	if (!data_file)
		free_and_exit_error(MALLOC_ERR_MSG);
	data->text_path = calloc_gc(4, sizeof(char **), TEXTURE);
	if (!data->text_path)
		free_and_exit_error(MALLOC_ERR_MSG);
	i = parse_texture_and_color_lines(data, data_file);
	extract_grid(&data->grid, &data_file[i]);
	clear_garbage(TMP, free);
}
