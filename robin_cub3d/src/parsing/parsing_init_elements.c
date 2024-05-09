/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init_elements.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:17:23 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 22:28:39 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_player_data(t_map *map, t_player *player)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	y = 1;
	while (map->map_strs[y] && y < map->height - 2)
	{
		while (map->map_strs[y][x])
		{
			if (map->map_strs[y][x] == 'N' || map->map_strs[y][x] == 'S'
				|| map->map_strs[y][x] == 'E' || map->map_strs[y][x] == 'W')
			{
				player->start_dir = map->map_strs[y][x];
				map->map_strs[y][x] = '0';
				player->posx = x;
				player->posy = y;
				return ;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	init_doors(t_cub3d *cub3d, t_map map)
{
	unsigned int	x;
	unsigned int	y;
	int				i;

	y = 0;
	i = 0;
	while (map.map_strs[y])
	{
		x = 0;
		while (map.map_strs[y][x])
		{
			if (map.map_strs[y][x] == 'D')
			{
				cub3d->doors[i].x = x;
				cub3d->doors[i].y = y;
				cub3d->doors[i].step_percent = 0;
				cub3d->doors[i].increment_step = 0;
				i++;
			}
			x++;
		}
		y++;
	}
}

void	alloc_doors(t_cub3d *cub3d, t_map map)
{
	unsigned int	x;
	unsigned int	y;

	cub3d->doors_nbr = 0;
	y = 0;
	while (map.map_strs[y])
	{
		x = 0;
		while (map.map_strs[y][x])
		{
			if (map.map_strs[y][x] == 'D')
				cub3d->doors_nbr++;
			x++;
		}
		y++;
	}
	if (mem_alloc(cub3d->doors_nbr * sizeof(t_door),
			(void **)&cub3d->doors, MAIN))
		error_message_and_exit(1, MALLOC_ERR_MSG);
}

bool	extrem_lines_are_correct(char *line)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			return (false);
		line++;
	}
	return (true);
}
