/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_config.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:24 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:57:27 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	init_ray(const double camera_x, t_player *player, t_ray *ray)
{
	ray->true_pos.x = player->pos.x;
	ray->true_pos.y = player->pos.y;
	ray->grid_pos.x = (int)player->pos.x;
	ray->grid_pos.y = (int)player->pos.y;
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
}

void	get_ray_config_dda(t_ray *r)
{
	r->delta_dist.x = fabs(1 / r->dir.x);
	r->delta_dist.y = fabs(1 / r->dir.y);
	if (r->dir.x < 0)
	{
		r->step_direction.x = -1;
		r->side_dist.x = (r->true_pos.x - r->grid_pos.x) * r->delta_dist.x;
	}
	else
	{
		r->step_direction.x = 1;
		r->side_dist.x = (r->grid_pos.x - r->true_pos.x + 1) * r->delta_dist.x;
	}
	if (r->dir.y < 0)
	{
		r->step_direction.y = -1;
		r->side_dist.y = (r->true_pos.y - r->grid_pos.y)
			* r->delta_dist.y;
	}
	else
	{
		r->step_direction.y = 1;
		r->side_dist.y = (r->grid_pos.y - r->true_pos.y + 1) * r->delta_dist.y;
	}
}
