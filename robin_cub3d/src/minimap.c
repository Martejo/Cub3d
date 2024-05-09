/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 22:15:12 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:06:21 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_img(t_tex *img, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(img->addr + ((x + y * SCREEN_WIDTH) * img->bpp)) = color;
}

static int	get_color(t_cub3d *cub3d, float x, float y)
{
	if (x < 0 || x >= cub3d->map_struct.width || y < 0
		|| y >= cub3d->map_struct.height)
		return (MINIMAP_OUTMAP_COLOR);
	if (cub3d->map_struct.map_strs[(int)y][(int)x] == '1')
		return (MINIMAP_WALL_COLOR);
	else if (cub3d->map_struct.map_strs[(int)y][(int)x] == '0')
		return (MINIMAP_FLOOR_COLOR);
	else
		return (MINIMAP_OUTMAP_COLOR);
}

static uint8_t	is_on_vector_line(t_cub3d *cub3d, float x, float y)
{
	float	x_proj;
	float	y_proj;

	x_proj = MINIMAP_CENTER + cub3d->player.dirx * DIRECTION_LINE_SIZE;
	y_proj = MINIMAP_CENTER + cub3d->player.diry * DIRECTION_LINE_SIZE;
	return (get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x, y)
		+ get_distance(x_proj, y_proj, x, y)
		> get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x_proj, y_proj)
		- DIRECTION_LINE_WIDTH
		&& get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x, y)
		+ get_distance(x_proj, y_proj, x, y)
		< get_distance(MINIMAP_CENTER, MINIMAP_CENTER, x_proj, y_proj)
		+ DIRECTION_LINE_WIDTH);
}

static uint8_t	is_on_center_square(int x, int y)
{
	int	square_begin_x;
	int	square_begin_y;
	int	square_size;

	square_begin_x = (MINIMAP_WIDTH / 2) - (PIXEL_PER_CUBE / 2);
	square_begin_y = (MINIMAP_HEIGHT / 2) - (PIXEL_PER_CUBE / 2);
	square_size = PIXEL_PER_CUBE;
	return (x >= square_begin_x && x < square_begin_x + square_size
		&& y >= square_begin_y && y < square_begin_y + square_size);
}

void	draw_minimap(t_cub3d *cub3d)
{
	int		x_pixel;
	int		y_pixel;
	float	x_map;
	float	y_map;

	y_pixel = -1;
	y_map = cub3d->player.posy - SIZE_AROUND_PLAYER;
	while (++y_pixel < MINIMAP_HEIGHT)
	{
		x_pixel = -1;
		x_map = cub3d->player.posx - SIZE_AROUND_PLAYER;
		while (++x_pixel < MINIMAP_WIDTH)
		{
			if (is_on_vector_line(cub3d, x_pixel, y_pixel)
				|| is_on_center_square(x_pixel, y_pixel))
				put_pixel_to_img(&cub3d->raycast_img, x_pixel,
					y_pixel, MINIMAP_PLAYER_COLOR);
			else
				put_pixel_to_img(&cub3d->raycast_img, x_pixel, y_pixel,
					get_color(cub3d, x_map, y_map));
			x_map += 1.0f / PIXEL_PER_CUBE;
		}
		y_map += 1.0f / PIXEL_PER_CUBE;
	}
}
