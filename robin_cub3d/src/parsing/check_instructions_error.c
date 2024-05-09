/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instructions_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 21:24:27 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 16:59:20 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	are_all_instructions_present(t_wall_textures textures)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (!textures.textures_paths[i])
			return (false);
		i++;
	}
	return (true);
}

void	convert_string_to_color(char *str_color, t_color *color)
{
	char	**strs;
	int		i;

	i = 0;
	strs = ft_split(str_color, ",", LOOP);
	while (strs[i])
	{
		if (!is_str_digit(strs[i]) || is_int_overflow(strs[i]))
			error_message_and_exit(1, COLOR_FORMAT_ERROR);
		else if (i < 3)
			color->octet[i] = ft_atoi(strs[i]);
		i++;
	}
	if (i != 3)
		error_message_and_exit(1, COLOR_FORMAT_ERROR);
}

bool	are_color_instruction_valid(t_wall_textures *textures)
{
	int	i;

	i = 4;
	while (i < 6)
	{
		convert_string_to_color(textures->textures_paths[i],
			&textures->colors[i % 4]);
		if (textures->colors[i % 4].octet[0] > 255
			|| textures->colors[i % 4].octet[1] > 255
			|| textures->colors[i % 4].octet[2] > 255)
			return (false);
		i++;
	}
	return (true);
}
