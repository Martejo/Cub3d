#include "../../includes/cub3d.h"


static bool	map_charset_is_correct(char **map)
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

static bool	extrem_lines_are_correct(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (false);
		line++;
	}
	return (true);
}

static bool	ground_is_surronded_by_walls(char **map)
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
			if (char_is_next_space(map, x, y))
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
	if (!extrem_lines_are_correct(map[0])
		|| !extrem_lines_are_correct(map[get_size_map(map) - 1]))
		return (false);
	if (!ground_is_surronded_by_walls(map) || !map_charset_is_correct(map))
		return (false);
	return (true);
}

char	**extract_map(char **map)
{
	char	**ret_map;
	int		i;

	if (is_valid_map(map))
	{
		ret_map = calloc_gc(get_size_map(map) + 1, sizeof(char **), ARRAY);
		i = 0;
		while (map[i])
		{
			ret_map[i] = strdup_gc(map[i], ARRAY);
			i++;
		}
		ret_map[i] = NULL;
	}
	else
		free_and_exit_error(MAP_ERROR);
	return (ret_map);
}