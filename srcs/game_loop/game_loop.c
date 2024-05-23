#include "../../includes/cub3d.h"

void create_raycast_img(t_cub3d *data)
{
    t_ray ray;
    t_player *player = &(data->player);
    t_dda wall_ray;
    double camera_x;

    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        init_ray(camera_x, player, &ray);
        get_ray_config_dda(&ray);
        get_wall_config_dda(&(data->player), &(data->grid), &ray, &wall_ray);
        add_pixels_col_to_img(data, x, &wall_ray);
    }
}

void game_loop(t_cub3d *data)
{
	create_raycast_img(data);
    mlx_hook(data->mlx.win_ptr, 2, 1L << 0, modif_player, data);
    mlx_loop(data->mlx.mlx_ptr);
}