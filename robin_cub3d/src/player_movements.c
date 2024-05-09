/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:54:44 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:06:21 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	update_cam(t_cub3d *cub3d, t_player *player, int sign, float speed)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = player->dirx;
	old_planex = cub3d->raycast.planex;
	player->dirx = player->dirx * cos(cub3d->camera_speed * speed * sign)
		- player->diry * sin(cub3d->camera_speed * speed * sign);
	player->diry = old_dirx * sin(cub3d->camera_speed * speed * sign)
		+ player->diry * cos(cub3d->camera_speed * speed * sign);
	cub3d->raycast.planex = cub3d->raycast.planex
		* cos(cub3d->camera_speed * speed * sign) - cub3d->raycast.planey
		* sin(cub3d->camera_speed * speed * sign);
	cub3d->raycast.planey = old_planex * sin(cub3d->camera_speed * speed * sign)
		+ cub3d->raycast.planey * cos(cub3d->camera_speed * speed * sign);
}

void	move_vision(t_cub3d *cub3d, t_player *player)
{
	int		x;
	int		y;
	float	speed;

	mlx_mouse_get_pos(cub3d->mlx, cub3d->mlx_win, &x, &y);
	if (ft_absf(x - SCREEN_WIDTH / 2) > 0 && cub3d->mouse_set)
		speed = ft_absf(x - SCREEN_WIDTH / 2) / 2;
	else
		speed = 1;
	if ((x > SCREEN_WIDTH / 2 && cub3d->mouse_set)
		|| (cub3d->keyboard.right_rotate && !cub3d->keyboard.left_rotate))
		update_cam(cub3d, player, 1, speed);
	else if ((x < SCREEN_WIDTH / 2 && cub3d->mouse_set)
		|| (cub3d->keyboard.left_rotate && !cub3d->keyboard.right_rotate))
		update_cam(cub3d, player, -1, speed);
}

static void	move_forward_back(t_cub3d *cub3d, t_player *player, int sign)
{
	if (hitbox_wallhit(cub3d, player->posx, player->posy
			+ (player->diry * cub3d->move_speed * sign)))
		player->posy += player->diry * cub3d->move_speed * sign;
	if (hitbox_wallhit(cub3d, player->posx
			+ (player->dirx * cub3d->move_speed * sign), player->posy))
		player->posx += player->dirx * cub3d->move_speed * sign;
}

static void	move_right_left(t_cub3d *cub3d, t_player *player, int sign)
{
	double	old_dirx;

	old_dirx = player->dirx;
	if (hitbox_wallhit(cub3d, player->posx
			+ ((player->dirx * cos(ROTATION_ANGLE * sign) - player->diry
					* sin(ROTATION_ANGLE * sign)) * cub3d->move_speed),
			player->posy))
		player->posx += (player->dirx * cos(ROTATION_ANGLE * sign)
				- player->diry * sin(ROTATION_ANGLE * sign))
			* cub3d->move_speed;
	if (hitbox_wallhit(cub3d, player->posx, player->posy + (old_dirx
				* sin(ROTATION_ANGLE * sign) + player->diry
				* cos(ROTATION_ANGLE * sign)) * cub3d->move_speed))
		player->posy += (old_dirx * sin(ROTATION_ANGLE * sign) + player->diry
				* cos(ROTATION_ANGLE * sign)) * cub3d->move_speed;
}

void	move_player(t_cub3d *cub3d, t_player *player)
{
	if (cub3d->keyboard.top && !cub3d->keyboard.bottom)
		move_forward_back(cub3d, player, 1);
	else if (cub3d->keyboard.bottom && !cub3d->keyboard.top)
		move_forward_back(cub3d, player, -1);
	if (cub3d->keyboard.right && !cub3d->keyboard.left)
		move_right_left(cub3d, player, 1);
	else if (cub3d->keyboard.left && !cub3d->keyboard.right)
		move_right_left(cub3d, player, -1);
}
