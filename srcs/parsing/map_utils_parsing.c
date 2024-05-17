/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:58:40 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/17 10:59:00 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

bool	is_space_line(char *str)
{
	int		i;
	bool	all_line_char_are_spaces;

	i = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	all_line_char_are_spaces = (str[i] == '\0');
	return (all_line_char_are_spaces);
}

int	get_size_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

bool	is_char_adjacent_to_space(char **map, int x, int y)
{
	if ((map[y][x] == '0' || map[y][x] == 'N'
		|| map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W'
		|| map[y][x] == 'D')
		&& (map[y][x + 1] == ' ' || map[y][x + 1] == '\0'
		|| map[y][x - 1] == ' '
		|| map[y + 1][x] == ' '
		|| map[y - 1][x] == ' '))
		return (true);
	return (false);
}
