#include "../includes/cub3d.h"

void	exit_error(t_cub3d *c3d, char *err)
{
	ft_putstr_fd(err, 2);
	clean_prog(c3d);
	exit(EXIT_FAILURE);
}

int	exit_button(t_cub3d *c3d)
{
	exit_game(c3d, END_PLAYER, EXIT_SUCCESS);
	return (0);
}

void	exit_game(t_cub3d *c3d, char *msg, int exit_status)
{
	int	i;

	mlx_destroy_window(c3d->mlx, c3d->mlx_win);
	if (c3d->raycast_img.img)
		mlx_destroy_image(c3d->mlx, c3d->raycast_img.img);
	i = -1;
	while (++i < 8)
	{
		if (i < 4 && c3d->sprites[i].reference)
			mlx_destroy_image(c3d->mlx, c3d->sprites[i].reference);
		if (c3d->torch_sprites[i].reference)
			mlx_destroy_image(c3d->mlx, c3d->torch_sprites[i].reference);
	}
	if (BONUS_FLAG && c3d->doors_nbr && c3d->sprites[4].reference) //que contient cette partie bonus ?
		mlx_destroy_image(c3d->mlx, c3d->sprites[4].reference);
	mlx_destroy_display(c3d->mlx);
	del_garbage(0); //que contient garbage(0) ?
	del_garbage(LOOP);
	if (exit_status == 0)
		ft_putendl_fd(msg, 1);
	else
		ft_putendl_fd(msg, 2);
	exit(exit_status);
}