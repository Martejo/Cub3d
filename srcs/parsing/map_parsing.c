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

static bool	is_map_enclosed_by_walls(char **grid, int height)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 1;
	while (grid[y] && y < height)
	{
		while (grid[y][x])
		{
			if ((x == 0 && grid[y][x] != '1'
				&& grid[y][x] != ' ')
				|| is_space_line(grid[y]))
				return (false);
			if (is_char_adjacent_to_space(grid, x, y))
				return (false);
			x++;
		}
		x = 0;
		y++;
	}
	return (true);
}

static bool	is_valid_map(char **grid, int height)
{
	if (!extrem_lines_are_valid(grid[0])
		|| !extrem_lines_are_valid(grid[height - 1]))
		return (false);
	if (!is_map_enclosed_by_walls(grid, height) || !is_map_charset_valid(grid))
		return (false);
	return (true);
}

void	extract_grid(t_grid *grid, char **grid_in_file)
{
	char	**ret_map;
	int		i;
	int		height;

	height = get_height_grid(grid_in_file);
	if (is_valid_map(grid_in_file, height))
	{
		ret_map = calloc_gc(height + 1, sizeof(char **), GRID);
		if (!ret_map)
			free_and_exit_error(MALLOC_ERR_MSG);
		i = -1;
		while (grid_in_file[++i])
		{
			ret_map[i] = strdup_gc(grid_in_file[i], GRID);
			if (!ret_map[i])
				free_and_exit_error(MALLOC_ERR_MSG);
		}
		ret_map[i] = NULL;
	}
	else
		free_and_exit_error(MAP_ERROR);
	grid->height = height;
	grid->width = get_max_width_grid(ret_map);
	grid->content = ret_map;
}
