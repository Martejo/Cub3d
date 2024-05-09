/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:03:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:27:47 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_and_exit(int exit_code)
{
	del_garbage(MAIN);
	del_garbage(LOOP);
	exit(exit_code);
}

void	error_message_and_exit(int exit_code, char *message)
{
	printf(RED "Error\n%s\n" RESET, message);
	free_and_exit(exit_code);
}

int	exit_button(t_cub3d *cub3d)
{
	exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
	return (0);
}

void	exit_game(t_cub3d *cub3d, char *msg, int exit_status)
{
	int	i;

	mlx_destroy_window(cub3d->mlx, cub3d->mlx_win);
	if (cub3d->raycast_img.img)
		mlx_destroy_image(cub3d->mlx, cub3d->raycast_img.img);
	i = -1;
	while (++i < 8)
	{
		if (i < 4 && cub3d->sprites[i].reference)
			mlx_destroy_image(cub3d->mlx, cub3d->sprites[i].reference);
		if (cub3d->torch_sprites[i].reference)
			mlx_destroy_image(cub3d->mlx, cub3d->torch_sprites[i].reference);
	}
	if (BONUS_FLAG && cub3d->doors_nbr && cub3d->sprites[4].reference)
		mlx_destroy_image(cub3d->mlx, cub3d->sprites[4].reference);
	mlx_destroy_display(cub3d->mlx);
	del_garbage(0);
	del_garbage(LOOP);
	if (exit_status == 0)
		ft_putendl_fd(msg, 1);
	else
		ft_putendl_fd(msg, 2);
	exit(exit_status);
}
