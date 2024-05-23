#include "../../includes/cub3d.h"

static int color_to_display(char wall_orientation)
{
    if (wall_orientation == 'N')
        return 0xFF0000; // Red
    else if (wall_orientation == 'S')
        return 0x00FF00; // Green
    else if (wall_orientation == 'E')
        return 0x0000FF; // Blue
    return 0xFFFF00; // Yellow
}

void add_pixels_col_to_img(t_cub3d *data, const int pixel_x, const t_dda *wall_config)
{
    int displayed_height;
    int pixel_y;
    int color;

    color = color_to_display(wall_config->orientation);
    displayed_height = (int)(SCREEN_HEIGHT / wall_config->dist);
    pixel_y = (SCREEN_HEIGHT - displayed_height) / 2;

    while (pixel_y < (SCREEN_HEIGHT + displayed_height) / 2)
    {
        mlx_pixel_put(data->mlx.mlx_ptr, data->mlx.win_ptr, pixel_x, pixel_y, color);
        pixel_y++;
    }
}