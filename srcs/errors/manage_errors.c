#include "../../includes/cub3d.h"

void	print_and_exit_error(char *msg)
{
	ft_printf_fd(2, "%s%s%s\n", RED, msg, RESET);
	exit(EXIT_FAILURE);
}

void	free_and_exit_error(char *msg)
{
	ft_printf_fd(2, "%s%s%s\n", RED, msg, RESET);
	clear_garbage(TEXTURE, free);
	clear_garbage(GRID, free);
	clear_garbage(TMP, free);
	clear_garbage(STRUCT, free);
	exit(EXIT_FAILURE);
}

void	close_programm(t_cub3d *cub3d, char *msg, int exit_code)
{
	int	i;

	i = 0;
	if (msg)
		ft_printf_fd(2, "%s%s%s\n", RED, msg, RESET);
	if (cub3d->framebuffer.img_ptr)
		mlx_destroy_image(cub3d->mlx.mlx_ptr, cub3d->framebuffer.img_ptr);
	while (i < 4)
	{
		if (cub3d->text_img[i].reference)
			mlx_destroy_image(cub3d->mlx.mlx_ptr, cub3d->text_img[i].reference);
		i++;
	}
	if (cub3d->mlx.win_ptr)
		mlx_destroy_window(cub3d->mlx.mlx_ptr, cub3d->mlx.win_ptr);
	if (cub3d->mlx.mlx_ptr)
		mlx_destroy_display(cub3d->mlx.mlx_ptr);
	clear_garbage(TEXTURE, free);
	clear_garbage(GRID, free);
	clear_garbage(TMP, free);
	clear_garbage(MLX, free);
	clear_garbage(STRUCT, free);
	exit(exit_code);
}
