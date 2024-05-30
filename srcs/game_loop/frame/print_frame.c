/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_frame.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:56:59 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:57:01 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

void	put_pixel(t_image *img, int col, int line, int color)
{
	int	offset;

	offset = (img->line_len * line) + (img->bpp * col / 8);
	if (col >= 0 && col < SCREEN_WIDTH && line >= 0 && line < SCREEN_HEIGHT)
		*((int *)(img->addr + offset)) = color;
}

void	draw_floor_ceil(t_cub3d *data, t_image *img)
{
	int	i;
	int	j;
	int	half_screen_height;

	half_screen_height = SCREEN_HEIGHT / 2;
	i = 0;
	while (i < half_screen_height)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			put_pixel(img, j, i, data->colors.ceiling_color);
		i++;
	}
	while (i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
			put_pixel(img, j, i, data->colors.floor_color);
		i++;
	}
}

static int	get_texture_x(t_ray *ray, t_dda *wall, t_texture *texture)
{
	double	wall_hit_pos;
	int		tex_x;

	if (wall->orientation == 'N' || wall->orientation == 'S')
		wall_hit_pos = ray->true_pos.x + wall->dist * ray->dir.x;
	else
		wall_hit_pos = ray->true_pos.y + wall->dist * ray->dir.y;
	wall_hit_pos -= floor(wall_hit_pos);
	tex_x = (int)(wall_hit_pos * (double)texture->x);
	return (tex_x);
}

static t_texture	*texture_to_display(t_cub3d *data, char wall_orientation)
{
	if (wall_orientation == 'N')
		return (&data->text_img[NORTH]);
	else if (wall_orientation == 'S')
		return (&data->text_img[SOUTH]);
	else if (wall_orientation == 'E')
		return (&data->text_img[EAST]);
	else if (wall_orientation == 'W')
		return (&data->text_img[WEST]);
	return (NULL);
}

void	add_pixels_col_to_img_txt(t_cub3d *data, int x,
	t_dda *wall_config, t_ray *ray)
{
	int				i;
	t_texture		*texture;
	t_pixel_column	c;

	texture = texture_to_display(data, wall_config->orientation);
	c.tex_x = get_texture_x(ray, wall_config, texture);
	c.height = (int)(SCREEN_HEIGHT / wall_config->dist);
	c.y_start = (SCREEN_HEIGHT - c.height) / 2;
	c.y_end = c.y_start + c.height;
	i = c.y_start;
	while (i < c.y_end)
	{
		c.tex_y = ((i - c.y_start) * texture->y) / c.height;
		c.color = *((int *)(texture->pixels + c.tex_y * texture->line_len
					+ c.tex_x * (texture->bits_per_pixel / 8)));
		put_pixel(&data->framebuffer, x, i, c.color);
		i++;
	}
}
