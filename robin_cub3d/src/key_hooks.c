/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:50:07 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 19:52:49 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	speed_key(t_cub3d *cub3d, int key)
{
	if (key == PLUS)
	{
		if (cub3d->move_speed + 0.02f < 0.5f)
			cub3d->move_speed += 0.02f;
		if (cub3d->move_speed + 0.01f < 0.2f)
			cub3d->camera_speed += 0.01f;
	}
	else if (key == MINUS)
	{
		if (cub3d->move_speed - 0.02f > 0.01f)
			cub3d->move_speed -= 0.02f;
		if (cub3d->camera_speed - 0.01f > 0.01f)
			cub3d->camera_speed -= 0.01f;
	}
}

int	key_press_hook(int key, t_cub3d *cub3d)
{
	if (key == D)
		cub3d->keyboard.right = 1;
	else if (key == A)
		cub3d->keyboard.left = 1;
	else if (key == W || key == TOP)
		cub3d->keyboard.top = 1;
	else if (key == S || key == BOTTOM)
		cub3d->keyboard.bottom = 1;
	else if (key == RIGHT)
		cub3d->keyboard.right_rotate = 1;
	else if (key == LEFT)
		cub3d->keyboard.left_rotate = 1;
	else if (key == CTRL && BONUS_FLAG)
		set_mouse(cub3d);
	else if (key == ESC)
		exit_game(cub3d, "Game exited by user.", EXIT_SUCCESS);
	else if (key == PLUS || key == MINUS)
		speed_key(cub3d, key);
	return (0);
}

static void	space_key(t_cub3d *cub3d)
{
	t_door	*door;

	door = targeted_door(cub3d);
	if (door)
	{
		if (door->step_percent == 0 && !is_on_door(cub3d, door))
		{
			door->step_percent = 1;
			door->increment_step = 1;
		}
		else if (door->step_percent == 100 && !is_on_door(cub3d, door))
		{
			door->step_percent = 99;
			door->increment_step = -1;
			cub3d->map_struct.map_strs[door->y][door->x] = 'D';
		}
	}
}

int	key_release_hook(int key, t_cub3d *cub3d)
{
	if (key == D)
		cub3d->keyboard.right = 0;
	else if (key == A)
		cub3d->keyboard.left = 0;
	else if (key == W || key == TOP)
		cub3d->keyboard.top = 0;
	else if (key == S || key == BOTTOM)
		cub3d->keyboard.bottom = 0;
	else if (key == RIGHT)
		cub3d->keyboard.right_rotate = 0;
	else if (key == LEFT)
		cub3d->keyboard.left_rotate = 0;
	else if (key == SPACE)
		space_key(cub3d);
	return (0);
}
