#include "../../includes/cub3d.h"

static double get_player_dir_relative_angle(char orientation)
{
	if (orientation == 'W')
		return(to_rad(0));
	else if (orientation == 'S')
		return(to_rad(90));
	else if (orientation == 'E')
		return(to_rad(180));
	else //N
		return(to_rad(270));
}

static t_dvector get_player_pos(const t_grid *grid)
{
	int	i;
	int	j;

	i = 0;
	while(grid->content[i])
	{
		j = 0;
		while(grid->content[i][j])
		{
			if (is_player(grid->content[i][j]))
				return((t_dvector){.x = j, .y = i});
			j++;
		}
		i++;
	}
}

static void	adjust_player_pos_to_near_walls(char **grid_c, t_player *player)
{
	//si le player est coll'e au mur, le mur ne sera pas affiche
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
	player->dir_angle = get_player_dir_relative_angle(grid->content[(int)player->pos.y][(int)player->pos.x]);
	adjust_player_pos_to_near_walls(grid->content, player);
	process_player_dir(player);
    process_player_plane(player);
    process_player_movement(player);
}