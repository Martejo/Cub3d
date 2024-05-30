/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_management.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:56:51 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:56:55 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

int	key_press_hook(int key, t_cub3d *data)
{
	if (key == XK_w)
		data->key.w = 1;
	else if (key == XK_s)
		data->key.s = 1;
	else if (key == XK_a)
		data->key.a = 1;
	else if (key == XK_d)
		data->key.d = 1;
	else if (key == XK_Left)
		data->key.left = 1;
	else if (key == XK_Right)
		data->key.right = 1;
	else if (key == XK_Escape)
		close_programm(data, "Close program", EXIT_SUCCESS);
	return (0);
}

int	key_release_hook(int key, t_cub3d *data)
{
	if (key == XK_w)
		data->key.w = 0;
	else if (key == XK_s)
		data->key.s = 0;
	else if (key == XK_a)
		data->key.a = 0;
	else if (key == XK_d)
		data->key.d = 0;
	else if (key == XK_Left)
		data->key.left = 0;
	else if (key == XK_Right)
		data->key.right = 0;
	return (0);
}

int	exit_button(t_cub3d *cub3d)
{
	close_programm(cub3d, "Game exited by user.", EXIT_SUCCESS);
	return (0);
}
