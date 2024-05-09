/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:21:40 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:04:05 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

float	get_distance(float x1, float y1, float x2, float y2)
{
	return (sqrtf(powf(x1 - x2, 2) + powf(y1 - y2, 2)));
}

void	find_pix(t_cub3d *cub, int y, unsigned char **pix, t_image *sprite)
{
	*pix = &sprite->pixels[(int)(y * sprite->line_len + cub->raycast.texx
			* (sprite->bits_per_pixel / 8) + sprite->line_len
			* (1 - get_open_percentage(cub)) - ((int)(sprite->line_len
					* (1 - get_open_percentage(cub)))
				% (sprite->bits_per_pixel / 8)))];
}
