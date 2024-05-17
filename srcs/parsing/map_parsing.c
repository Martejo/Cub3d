/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:56:55 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/17 15:49:52 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static bool	is_map_charset_valid(char **map)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	player_charset_nbr;

	player_charset_nbr = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				player_charset_nbr++;
			else if (map[y][x] != '0' && map[y][x] != '1'
				&& map[y][x] != ' ')
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (player_charset_nbr == 1);
}

static bool	extrem_lines_are_valid(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (false);
		line++;
	}
	return (true);
}

static bool	is_map_enclosed_by_walls(char **map)
{
	unsigned int	x;
	unsigned int	y;
	int				size;

	size = get_size_map(map);
	x = 0;
	y = 1;
	while (map[y] && y < size)
	{
		while (map[y][x])
		{
			if ((x == 0 && map[y][x] != '1'
				&& map[y][x] != ' ')
				|| is_space_line(map[y]))
				return (false);
			if (is_char_adjacent_to_space(map, x, y))
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (true);
}

static bool	is_valid_map(char **map)
{
	if (!extrem_lines_are_valid(map[0])
		|| !extrem_lines_are_valid(map[get_size_map(map) - 1]))
		return (false);
	if (!is_map_enclosed_by_walls(map) || !is_map_charset_valid(map))
		return (false);
	return (true);
}

char	**extract_map(char **map)
{
	char	**ret_map;
	int		i;

	if (is_valid_map(map))
	{
		ret_map = calloc_gc(get_size_map(map) + 1, sizeof(char **), GRID);
		i = 0;
		while (map[i])
		{
			ret_map[i] = strdup_gc(map[i], GRID);
			i++;
		}
		ret_map[i] = NULL;
	}
	else
		free_and_exit_error(MAP_ERROR);
	return (ret_map);
}
