#include "../../includes/cub3d.h"

void	init_image(t_cub3d *data)
{
	data->framebuffer.img_ptr = mlx_new_image(data->mlx.mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->framebuffer.img_ptr)
		free_and_exit_error("que\n"); // A voir changer msg
	data->framebuffer.addr = mlx_get_data_addr(data->framebuffer.img_ptr, &data->framebuffer.bpp, &data->framebuffer.line_length, &data->framebuffer.endian);

	/*
	bpp (bits par pixel) est initialement donné en bits.
	En le divisant par 8, on le convertit en octets par pixel,
	ce qui est plus pratique pour la manipulation des données de l'image.
	*/
	data->framebuffer.bpp /= 8;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		free_and_exit_error(MALLOC_ERR_MSG); //changer msg
	add_to_garbage(mlx->mlx_ptr, MLX);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}