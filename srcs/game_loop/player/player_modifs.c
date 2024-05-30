/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_modifs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:13 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:57:15 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

static bool	try_move(t_grid *grid, t_dvector *pos, double dx, double dy)
{
	t_dvector	new;
	t_ivector	grid_pos;
	t_ivector	grid_pos2;

	new.x = pos->x + dx;
	new.y = pos->y + dy;
	grid_pos.x = (int)(new.x + 0.3);
	grid_pos2.x = (int)(new.x - 0.3);
	grid_pos.y = (int)(new.y + 0.3);
	grid_pos2.y = (int)(new.y - 0.3);
	if (grid_pos.x < 0 || grid_pos.x >= grid->width || grid_pos.y < 0
		|| grid_pos.y >= grid->height || grid_pos2.x < 0
		|| grid_pos2.x >= grid->width || grid_pos2.y < 0
		|| grid_pos2.y >= grid->height)
		return (false);
	if (grid->content[grid_pos.y][grid_pos.x] != '1'
		&& grid->content[grid_pos2.y][grid_pos.x] != '1'
		&& grid->content[grid_pos.y][grid_pos2.x] != '1'
		&& grid->content[grid_pos2.y][grid_pos2.x] != '1')
	{
		pos->x = new.x;
		pos->y = new.y;
		return (true);
	}
	return (false);
}

static void	key_manage_wasd(const t_key_handl *key, t_player *player,
				t_dvector *move_wanted)
{
	if (key->w == 1)
	{
		move_wanted->x = player->movement.x;
		move_wanted->y = player->movement.y;
	}
	else if (key->s == 1)
	{
		move_wanted->x = -player->movement.x;
		move_wanted->y = -player->movement.y;
	}
	else if (key->a == 1)
	{
		move_wanted->x = player->movement.y;
		move_wanted->y = -player->movement.x;
	}
	else if (key->d == 1)
	{
		move_wanted->x = -player->movement.y;
		move_wanted->y = player->movement.x;
	}
}

static void	modif_player_pos(t_key_handl *key, t_player *player, t_grid *grid)
{
	t_dvector	move_wanted;
	t_dvector	new;

	new.x = player->pos.x;
	new.y = player->pos.y;
	move_wanted = (t_dvector){0, 0};
	key_manage_wasd(key, player, &move_wanted);
	if (!try_move(grid, &new, move_wanted.x, move_wanted.y))
	{
		if (!try_move(grid, &new, move_wanted.x, 0))
			try_move(grid, &new, 0, move_wanted.y);
	}
	player->pos.x = new.x;
	player->pos.y = new.y;
}

static void	modif_player_dir(t_key_handl *key, t_player *player)
{
	if (key->left == 1)
	{
		player->dir_angle -= PLAYER_ROT_SPEED;
		if (player->dir_angle < 0)
			player->dir_angle += 2 * PI;
	}
	if (key->right == 1)
	{
		player->dir_angle += PLAYER_ROT_SPEED;
		if (player->dir_angle > 2 * PI)
			player->dir_angle -= 2 * PI;
	}
	process_player_dir(player);
	process_player_plane(player);
	process_player_movement(player);
}

int	modif_player(t_cub3d *data)
{
	modif_player_pos(&(data->key), &(data->player), &(data->grid));
	modif_player_dir(&(data->key), &(data->player));
	return (0);
}
