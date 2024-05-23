#include "../../includes/cub3d.h"

void    draw_floor_ceil(t_cub3d *data, t_image *img)
{
    int i;
    int j;

    i = 0;
    while(i < SCREEN_HEIGHT / 2)
    {
        j = 0;
        while ( j < SCREEN_WIDTH)
        {
            put_pixel(img, j, i, data->colors.ceiling_color);
            j++;
        }
        i++;
    }

    while(i < SCREEN_HEIGHT)
    {
        j = 0;
        while ( j < SCREEN_WIDTH)
        {
            put_pixel(img, j, i, data->colors.floor_color);
            j++;
        }
        i++;
    }
}


void create_raycast_img(t_cub3d *data)
{
    t_ray ray;
    t_player *player = &(data->player);
    t_dda wall_ray;
    double camera_x;

    draw_floor_ceil(data, &data->framebuffer);
    for (int x = 0; x < SCREEN_WIDTH; x++)
    {
        camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        init_ray(camera_x, player, &ray);
        get_ray_config_dda(&ray);
        get_wall_config_dda(&(data->player), &(data->grid), &ray, &wall_ray);
        add_pixels_col_to_img(data, x, &wall_ray);
    }
    mlx_put_image_to_window(data->mlx.mlx_ptr, data->mlx.win_ptr, data->framebuffer.img_ptr, 0, 0);
}

void game_loop(t_cub3d *data)
{
	create_raycast_img(data);
    mlx_hook(data->mlx.win_ptr, 2, 1L << 0, modif_player, data);
    mlx_loop(data->mlx.mlx_ptr);
}