#include "../../includes/cub3d.h"

void	create_raycast_img(t_cub3d *data)
{
	t_ray		ray;
	t_player	*player;
	t_dda		wall_ray;
	double		camera_x;
	int			x;

	x = 0;
	player = &(data->player);
	draw_floor_ceil(data, &data->framebuffer);
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		init_ray(camera_x, player, &ray);
		get_ray_config_dda(&ray);
		get_wall_config_dda(&(data->grid), &ray, &wall_ray);
		add_pixels_col_to_img_txt(data, x, &wall_ray, &ray);
		x++;
	}
	mlx_put_image_to_window(data->mlx.mlx_ptr,
		data->mlx.win_ptr, data->framebuffer.img_ptr, 0, 0);
}

int	game_loop(t_cub3d *data)
{
	modif_player(data);
	create_raycast_img(data);
	return (0);
}

void	game_event_loop(t_cub3d *data)
{
	mlx_hook(data->mlx.win_ptr, 17, 0L, exit_button, data);
	mlx_hook(data->mlx.win_ptr, 02, 1L << 0, key_press_hook, data);
	mlx_hook(data->mlx.win_ptr, 03, 1L << 1, key_release_hook, data);
	mlx_loop_hook(data->mlx.mlx_ptr, game_loop, (void *)data);
	mlx_loop(data->mlx.mlx_ptr);
}
