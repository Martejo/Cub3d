/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 15:06:45 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:06:21 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*targeted_door(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->doors_nbr)
	{
		if (cub3d->player.dirx + cub3d->player.posx > cub3d->doors[i].x
			&& cub3d->player.dirx + cub3d->player.posx < cub3d->doors[i].x + 1
			&& cub3d->player.diry + cub3d->player.posy > cub3d->doors[i].y
			&& cub3d->player.diry + cub3d->player.posy < cub3d->doors[i].y + 1)
			return (&cub3d->doors[i]);
		i++;
	}
	return (NULL);
}

void	update_door_loop(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->doors_nbr)
	{
		if (cub3d->doors[i].step_percent > 0
			&& cub3d->doors[i].step_percent < 100)
			cub3d->doors[i].step_percent += cub3d->doors[i].increment_step;
		else if (cub3d->doors[i].step_percent == 100
			&& cub3d->map_struct.map_strs[cub3d->doors[i].y][cub3d->doors[i].x]
				== 'D')
			cub3d->map_struct.map_strs[cub3d->doors[i].y][cub3d->doors[i].x]
				= '0';
		i++;
	}
}

int	loop(t_cub3d *cub3d)
{
	move_vision(cub3d, &cub3d->player);
	if (BONUS_FLAG && cub3d->mouse_set)
		mlx_mouse_move(cub3d->mlx, cub3d->mlx_win,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	move_player(cub3d, &cub3d->player);
	update_door_loop(cub3d);
	raycast(cub3d, &cub3d->raycast);
	return (0);
}

void	game_loop(t_cub3d *cub3d)
{
	mlx_hook(cub3d->mlx_win, 17, 0L, exit_button, cub3d);
	mlx_hook(cub3d->mlx_win, 02, 1L << 0, key_press_hook, cub3d);
	mlx_hook(cub3d->mlx_win, 03, 1L << 1, key_release_hook, cub3d);
	mlx_loop_hook(cub3d->mlx, loop, (void *)cub3d);
	mlx_loop(cub3d->mlx);
}
