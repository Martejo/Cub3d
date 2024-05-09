/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 21:44:44 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 17:27:40 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	char_is_next_space(t_map map, int x, int y)
{
	if ((map.map_strs[y][x] == '0' || map.map_strs[y][x] == 'N'
		|| map.map_strs[y][x] == 'S'
		|| map.map_strs[y][x] == 'E' || map.map_strs[y][x] == 'W'
		|| map.map_strs[y][x] == 'D')
		&& (map.map_strs[y][x + 1] == ' ' || map.map_strs[y][x + 1] == '\0'
		|| map.map_strs[y][x - 1] == ' '
		|| map.map_strs[y + 1][x] == ' '
		|| map.map_strs[y - 1][x] == ' '))
		return (true);
	return (false);
}

bool	is_door_bettween_two_walls(t_map map, int x, int y)
{
	if (map.map_strs[y][x] == 'D'
		&& !((map.map_strs[y][x + 1] == '1' && map.map_strs[y][x - 1] == '1'
		&& map.map_strs[y - 1][x] == '0' && map.map_strs[y + 1][x] == '0')
		|| (map.map_strs[y][x + 1] == '0' && map.map_strs[y][x - 1] == '0'
		&& map.map_strs[y - 1][x] == '1' && map.map_strs[y + 1][x] == '1')))
		return (false);
	return (true);
}

bool	ground_is_surronded_by_walls(t_map map)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 1;
	while (map.map_strs[y] && y < map.height - 1)
	{
		while (map.map_strs[y][x])
		{
			if ((x == 0 && map.map_strs[y][x] != '1'
				&& map.map_strs[y][x] != ' ')
				|| is_space_line(map.map_strs[y]))
				return (false);
			if (char_is_next_space(map, x, y))
				return (false);
			if (!is_door_bettween_two_walls(map, x, y))
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (true);
}

bool	map_charset_is_correct(t_map map)
{
	unsigned int	x;
	unsigned int	y;
	unsigned int	player_charset_nbr;

	player_charset_nbr = 0;
	x = 0;
	y = 0;
	while (map.map_strs[y])
	{
		while (map.map_strs[y][x])
		{
			if (map.map_strs[y][x] == 'N' || map.map_strs[y][x] == 'S'
				|| map.map_strs[y][x] == 'E' || map.map_strs[y][x] == 'W')
				player_charset_nbr++;
			else if (BONUS_FLAG && map.map_strs[y][x] == 'D')
				;
			else if (map.map_strs[y][x] != '0' && map.map_strs[y][x] != '1'
				&& map.map_strs[y][x] != ' ')
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (player_charset_nbr == 1);
}

bool	is_valid_map(t_map map)
{
	if (map.width < 3 || map.height < 3)
		return (false);
	if (!extrem_lines_are_correct(map.map_strs[0])
		|| !extrem_lines_are_correct(map.map_strs[map.height - 1]))
		return (false);
	if (!ground_is_surronded_by_walls(map) || !map_charset_is_correct(map))
		return (false);
	return (true);
}
