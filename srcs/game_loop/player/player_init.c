/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:08 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:57:10 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static double	get_player_dir_relative_angle(char orientation)
{
	if (orientation == 'W')
		return (to_rad(0));
	else if (orientation == 'S')
		return (to_rad(90));
	else if (orientation == 'E')
		return (to_rad(180));
	else
		return (to_rad(270));
}

static t_dvector	get_player_pos(const t_grid *grid)
{
	int			i;
	int			j;
	t_dvector	pos;
	bool		flag;

	i = 0;
	flag = false;
	while (!flag && grid->content[i])
	{
		j = 0;
		while (!flag && grid->content[i][j])
		{
			if (is_player(grid->content[i][j]))
			{
				pos = (t_dvector){.x = j, .y = i};
				flag = true;
			}
			j++;
		}
		i++;
	}
	return (pos);
}

static void	adjust_player_pos_to_near_walls(char **grid_c, t_player *player)
{
	if (grid_c[(int)player->pos.y - 1][(int)player->pos.x])
		player->pos.y += 0.5;
	else if (grid_c[(int)player->pos.y + 1][(int)player->pos.x])
		player->pos.y -= 0.5;
	if (grid_c[(int)player->pos.y][(int)player->pos.x - 1])
		player->pos.x += 0.5;
	else if (grid_c[(int)player->pos.y][(int)player->pos.x + 1])
		player->pos.x -= 0.5;
}

void	init_player(t_grid *grid, t_player *player)
{
	player->pos = get_player_pos(grid);
	player->dir_angle = get_player_dir_relative_angle
		(grid->content[(int)player->pos.y][(int)player->pos.x]);
	adjust_player_pos_to_near_walls(grid->content, player);
	process_player_dir(player);
	process_player_plane(player);
	process_player_movement(player);
}
