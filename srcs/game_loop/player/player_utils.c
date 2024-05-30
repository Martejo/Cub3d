/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:18 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:57:20 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

bool	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

double	to_rad(int degrees)
{
	return (degrees * PI / 180);
}

void	process_player_movement(t_player *player)
{
	player->movement.x = cos(player->dir_angle) * PLAYER_STEP_SIZE;
	player->movement.y = sin(player->dir_angle) * PLAYER_STEP_SIZE;
}

void	process_player_dir(t_player *player)
{
	player->dir.x = cos(player->dir_angle);
	player->dir.y = sin(player->dir_angle);
}

void	process_player_plane(t_player *player)
{
	player->plane.x = -player->dir.y * PLANE_FOV;
	player->plane.y = player->dir.x * PLANE_FOV;
}
