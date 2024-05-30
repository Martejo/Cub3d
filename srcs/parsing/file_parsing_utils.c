/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:36:37 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/30 14:36:47 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_line(const char *str)
{
	while (*str == ' ')
		str++;
	return (*str == '1');
}

bool	is_charset_txt(char c)
{
	return (c == 'F' || c == 'C' || c == 'S'
		|| c == 'W' || c == 'E' || c == 'N');
}

int	find_start_map(char *str_file)
{
	int	start;
	int	line;

	start = 0;
	line = 0;
	while (str_file[start] && line < 6)
	{
		while (str_file[start] && str_file[start] == '\n')
			start++;
		while (str_file[start] && str_file[start] != '\n')
			start++;
		line++;
	}
	if (is_charset_txt(str_file[start + 1]))
		free_and_exit_error(CONFIG_ERROR);
	return (start);
}
