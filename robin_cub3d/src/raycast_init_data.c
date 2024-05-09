/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_init_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 19:03:44 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 22:06:21 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	conditional_inizialize(t_cub3d *cub3d, t_raycast *raycast)
{
	if (raycast->raydirx < 0)
	{
		raycast->stepx = -1;
		raycast->sidedistx = (cub3d->player.posx - raycast->mapx)
			* raycast->deltadistx;
	}
	else
	{
		raycast->stepx = 1;
		raycast->sidedistx = (raycast->mapx + 1.0 - cub3d->player.posx)
			* raycast->deltadistx;
	}
	if (raycast->raydiry < 0)
	{
		raycast->stepy = -1;
		raycast->sidedisty = (cub3d->player.posy - raycast->mapy)
			* raycast->deltadisty;
	}
	else
	{
		raycast->stepy = 1;
		raycast->sidedisty = (raycast->mapy + 1.0 - cub3d->player.posy)
			* raycast->deltadisty;
	}
}

void	raycast_initialize(t_cub3d *cub3d, t_raycast *raycast, int x)
{
	raycast->camerax = 2 * x / (double)SCREEN_WIDTH - 1;
	raycast->raydirx = cub3d->player.dirx + raycast->planex * raycast->camerax;
	raycast->raydiry = cub3d->player.diry + raycast->planey * raycast->camerax;
	raycast->mapx = (int)cub3d->player.posx;
	raycast->mapy = (int)cub3d->player.posy;
	raycast->deltadistx = 1e30;
	raycast->deltadisty = 1e30;
	raycast->hit = 0;
	if (raycast->raydirx != 0)
		raycast->deltadistx = fabs(1 / raycast->raydirx);
	if (raycast->raydiry != 0)
		raycast->deltadisty = fabs(1 / raycast->raydiry);
	conditional_inizialize(cub3d, raycast);
}

void	raycast_find_wall(t_cub3d *cub3d, t_raycast *raycast, int do_hit_door)
{
	while (raycast->hit == 0)
	{
		if (raycast->sidedistx < raycast->sidedisty)
		{
			raycast->sidedistx += raycast->deltadistx;
			raycast->mapx += raycast->stepx;
			raycast->side = 0;
		}
		else
		{
			raycast->sidedisty += raycast->deltadisty;
			raycast->mapy += raycast->stepy;
			raycast->side = 1;
		}
		if (cub3d->map_struct.map_strs[raycast->mapy][raycast->mapx] == '1'
			|| (do_hit_door == 1
			&& cub3d->map_struct.map_strs[raycast->mapy][raycast->mapx] == 'D'))
			raycast->hit = 1;
	}
	if (raycast->side == 0)
		raycast->perpwalldist = (raycast->sidedistx - raycast->deltadistx);
	else
		raycast->perpwalldist = (raycast->sidedisty - raycast->deltadisty);
}

void	find_texture_index(t_cub3d *cub3d)
{
	if (cub3d->map_struct
		.map_strs[cub3d->raycast.mapy][cub3d->raycast.mapx] == 'D')
		cub3d->raycast.texnum = 4;
	else if (cub3d->raycast.side == 1)
	{
		if (cub3d->raycast.raydiry >= 0)
			cub3d->raycast.texnum = 0;
		else
			cub3d->raycast.texnum = 1;
	}
	else
	{
		if (cub3d->raycast.raydirx >= 0)
			cub3d->raycast.texnum = 2;
		else
			cub3d->raycast.texnum = 3;
	}
}

void	texture_calculation(t_cub3d *cub3d)
{
	find_texture_index(cub3d);
	if (cub3d->raycast.side == 0)
	{
		cub3d->raycast.wallx = cub3d->player.posy + cub3d->raycast.perpwalldist
			* cub3d->raycast.raydiry;
	}
	else
	{
		cub3d->raycast.wallx = cub3d->player.posx + cub3d->raycast.perpwalldist
			* cub3d->raycast.raydirx;
	}
	cub3d->raycast.wallx -= floor((cub3d->raycast.wallx));
	cub3d->raycast.texx = (int)(cub3d->raycast.wallx
			* (double)cub3d->sprites[cub3d->raycast.texnum].x);
	if (cub3d->raycast.side == 0 && cub3d->raycast.raydirx > 0)
		cub3d->raycast.texx = cub3d->sprites[cub3d->raycast.texnum].x
			- cub3d->raycast.texx - 1;
	if (cub3d->raycast.side == 1 && cub3d->raycast.raydiry < 0)
		cub3d->raycast.texx = cub3d->sprites[cub3d->raycast.texnum].x
			- cub3d->raycast.texx - 1;
}
