/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitbox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:46:54 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:04:54 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint8_t	hitbox_wallhit(t_cub3d *cub3d, double x, double y)
{	
	return (cub3d->map_struct.map_strs[(int)y][(int)(x + HITBOX_SIZE)] == '0'
		&& cub3d->map_struct.map_strs[(int)y][(int)(x - HITBOX_SIZE)] == '0'
		&& cub3d->map_struct.map_strs[(int)(y + HITBOX_SIZE)][(int)x] == '0'
		&& cub3d->map_struct.map_strs[(int)(y - HITBOX_SIZE)][(int)x] == '0');
}

uint8_t	is_on_door(t_cub3d *cub3d, t_door *targeted_door)
{
	return (((int)targeted_door->x == (int)(cub3d->player.posx + HITBOX_SIZE)
		&& (int)targeted_door->y == (int)cub3d->player.posy)
		|| ((int)targeted_door->x == (int)(cub3d->player.posx - HITBOX_SIZE)
		&& (int)targeted_door->y == (int)cub3d->player.posy)
		|| ((int)targeted_door->x == (int)cub3d->player.posx
		&& (int)targeted_door->y == (int)(cub3d->player.posy + HITBOX_SIZE))
		|| ((int)targeted_door->x == (int)cub3d->player.posx
		&& (int)targeted_door->y == (int)(cub3d->player.posy - HITBOX_SIZE)));
}
