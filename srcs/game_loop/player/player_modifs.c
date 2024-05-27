#include "../../../includes/cub3d.h"

static bool	try_move(t_grid *grid, t_vector *pos, double dx, double dy)
{
	t_vector	new;
	t_ivector	grid_pos;
	t_ivector	grid_pos2;

	new.x = pos->x + dx;
	new.y = pos->y + dy;
	grid_pos.x = (int)(new.x + 0.25);
	grid_pos2.x = (int)(new.x - 0.25);
	grid_pos.y = (int)(new.y + 0.25);
	grid_pos2.y = (int)(new.y - 0.25);
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

static void	modif_player_pos(t_key_handl key, t_player *player, t_grid *grid)
{
	t_vector	delta;
	t_vector	new;

	new.x = player->pos.x;
	new.y = player->pos.y;
	delta.x = 0;
	delta.y = 0;
	if (key.key_w == 1)
	{
		delta.x = player->movement.x;
		delta.y = player->movement.y;
	}
	else if (key.key_s == 1)
	{
		delta.x = -player->movement.x;
		delta.y = -player->movement.y;
	}
	else if (key.key_a == 1)
	{
		delta.x = player->movement.y;
		delta.y = -player->movement.x;
	}
	else if (key.key_d == 1)
	{
		delta.x = -player->movement.y;
		delta.y = player->movement.x;
	}
	if (!try_move(grid, &new, delta.x, delta.y))
	{
		if (!try_move(grid, &new, delta.x, 0))
			try_move(grid, &new, 0, delta.y);
	}
	player->pos.x = new.x;
	player->pos.y = new.y;
}

static void	modif_player_dir(t_key_handl key, t_player *player)
{
	if (key.key_left == 1)
	{
		player->dir_angle -= 0.020;
		if (player->dir_angle < 0)
			player->dir_angle += 2 * PI;
	}
	if (key.key_right == 1)
	{
		player->dir_angle += 0.020;
		if (player->dir_angle > 2 * PI)
			player->dir_angle -= 2 * PI;
	}
	process_player_dir(player);
	process_player_plane(player);
	process_player_movement(player);
}

int	modif_player(t_cub3d *data)
{
	modif_player_pos(data->key, &(data->player), &(data->grid));
	modif_player_dir(data->key, &(data->player));
	return (0);
}
