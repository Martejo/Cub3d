/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 17:40:56 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 22:07:56 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	get_open_percentage(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->doors_nbr)
	{
		if ((int)cub3d->doors[i].x == cub3d->raycast.mapx
			&& (int)cub3d->doors[i].y == cub3d->raycast.mapy)
			return ((float)cub3d->doors[i].step_percent / 100);
		i++;
	}
	return (-1.0f);
}

static int	choose_texture_to_draw(t_cub3d *cub3d, int x, int i, double *texpos)
{
	unsigned char	*pixel;
	int				texy;
	t_image			sprite;

	sprite = cub3d->sprites[cub3d->raycast.texnum];
	texy = (int) *texpos & (cub3d->sprites[cub3d->raycast.texnum].y - 1);
	*texpos += 1.0 * cub3d->sprites[cub3d->raycast.texnum].y
		/ cub3d->raycast.lineheight;
	pixel = &sprite.pixels[texy * sprite.line_len + cub3d->raycast.texx
		* (sprite.bits_per_pixel / 8)];
	if (cub3d->raycast.texnum == 4 && cub3d->raycast.texx
		* (sprite.bits_per_pixel / 8) < sprite.line_len
		* get_open_percentage(cub3d))
		return (1);
	else if (cub3d->raycast.texnum == 4)
	{
		find_pix(cub3d, texy, &pixel, &sprite);
		put_pixel_to_img(&cub3d->raycast_img, x, i,
			get_trgb(0, pixel[2], pixel[1], pixel[0]));
	}
	else
		put_pixel_to_img(&cub3d->raycast_img, x, i,
			get_trgb(0, pixel[2], pixel[1], pixel[0]));
	return (0);
}

static int	draw_line(t_cub3d *cub3d, int x)
{
	int				i;
	double			step;
	double			texpos;
	int				reached_door_end;

	reached_door_end = 0;
	step = 1.0 * cub3d->sprites[cub3d->raycast.texnum].y
		/ cub3d->raycast.lineheight;
	texpos = (cub3d->raycast.drawstart - SCREEN_HEIGHT
			/ 2 + cub3d->raycast.lineheight / 2) * step;
	i = 0;
	while (i < SCREEN_HEIGHT)
	{
		if (i < cub3d->raycast.drawstart)
			put_pixel_to_img(&cub3d->raycast_img, x, i, cub3d->colors.sky);
		else if (i < cub3d->raycast.drawend)
			reached_door_end = choose_texture_to_draw(cub3d, x, i, &texpos);
		else
			put_pixel_to_img(&cub3d->raycast_img, x, i, cub3d->colors.floor);
		i++;
	}
	return (reached_door_end);
}

void	raycast_loop(t_cub3d *cub3d, t_raycast *raycast, int x, int *hit_door)
{
	raycast_initialize(cub3d, raycast, x);
	raycast_find_wall(cub3d, raycast, *hit_door);
	raycast->lineheight = (int)(SCREEN_HEIGHT / raycast->perpwalldist);
	raycast->drawstart = -raycast->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (raycast->drawstart < 0)
			raycast->drawstart = 0;
	raycast->drawend = raycast->lineheight / 2 + SCREEN_HEIGHT / 2;
	if (raycast->drawend >= SCREEN_HEIGHT)
			raycast->drawend = SCREEN_HEIGHT - 1;
	texture_calculation(cub3d);
	if (draw_line(cub3d, x))
		*hit_door = 0;
}

void	raycast(t_cub3d *cub3d, t_raycast *raycast)
{
	int	x;
	int	hit_door;

	x = 0;
	hit_door = 1;
	while (x < SCREEN_WIDTH)
	{
		raycast_loop(cub3d, raycast, x, &hit_door);
		x++;
	}
	draw_minimap(cub3d);
	insert_torch(cub3d);
	insert_flame(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->mlx_win,
		cub3d->raycast_img.img, 0, 0);
}
