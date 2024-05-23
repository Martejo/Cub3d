#include "../../includes/cub3d.h"

static bool is_valid_move(t_grid *grid, double new_x, double new_y)
{
    int grid_x = (int)new_x;
    int grid_y = (int)new_y;

    if (grid_x < 0 || grid_x >= grid->width || grid_y < 0 || grid_y >= grid->height)
    {
        return false; // Out of bounds
    }

    if (grid->content[grid_y][grid_x] == '1')
    {
        return false; // Collision with wall
    }

    return true;
}

static void modif_player_pos(int key, t_player *player, t_grid *grid)
{
    double new_x = player->pos.x;
    double new_y = player->pos.y;
    double movement_perp_x = player->movement.y;
    double movement_perp_y = -player->movement.x;

    if (key == XK_w)
    {
        new_x += player->movement.x;
        new_y += player->movement.y;
    }
    else if (key == XK_s)
    {
        new_x -= player->movement.x;
        new_y -= player->movement.y;
    }
    else if (key == XK_a)
    {
        new_x += movement_perp_x;
        new_y += movement_perp_y;
    }
    else if (key == XK_d)
    {
        new_x -= movement_perp_x;
        new_y -= movement_perp_y;
    }

    if (is_valid_move(grid, new_x, new_y))
    {
        player->pos.x = new_x;
        player->pos.y = new_y;
    }
}

static void modif_player_dir(int key, t_player *player)
{
    if (key == XK_Left)
    {
        player->dir_angle -= 0.1;
        if (player->dir_angle < 0)
            player->dir_angle += 2 * PI;
    }
    if (key == XK_Right)
    {
        player->dir_angle += 0.1;
        if (player->dir_angle > 2 * PI)
            player->dir_angle -= 2 * PI;
    }
    process_player_dir(player);
    process_player_plane(player);
    process_player_movement(player);
}

int	modif_player(int key, t_cub3d *data)
{
    mlx_clear_window(data->mlx.mlx_ptr, data->mlx.win_ptr);
    if (key == XK_w || key == XK_a || key == XK_s || key == XK_d)
        modif_player_pos(key, &(data->player), &(data->grid));
    if (key == XK_Left || key == XK_Right)
        modif_player_dir(key, &(data->player));
    //printf("posx = %f posy = %f angle = %f\n", data->player.pos.x, data->player.pos.y, data->player.dir_angle);//
   // fflush(stdout);//
    create_raycast_img(data);
	return (0);
}