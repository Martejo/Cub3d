/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_get_textures.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:15:01 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 16:46:15 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	find_cardinal_instructions(t_cub3d *prog, char *line, int card_index)
{
	char	*cardinal;

	cardinal = prog->wall_textures.cardinals_array[card_index];
	if (!ft_strncmp(line, cardinal, ft_strlen(cardinal)))
	{
		prog->wall_textures.textures_paths[card_index]
			= &line[ft_strlen(prog->wall_textures.cardinals_array[card_index])];
		prog->wall_textures.textures_paths[card_index]
			= ft_strtrim(prog->wall_textures.textures_paths[card_index],
				" ", MAIN);
		return (true);
	}
	return (false);
}

bool	parse_wall_textures(t_cub3d *prog)
{
	int	line_index;

	line_index = 0;
	while (line_index < 6 && prog->file_to_strs[line_index])
	{
		if (!find_cardinal_instructions(prog, prog->file_to_strs[line_index],
				line_index))
			error_message_and_exit(1, TEXTURES_INSTRUCTION_ERROR);
		line_index++;
	}
	return (true);
}
