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
	// if ((wall->orientation == 'N' && ray->dir.x > 0)
	// 	|| (wall->orientation == 'S' && ray->dir.y < 0))
	// 	tex_x = texture->x - tex_x - 1;
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

void	add_pixels_col_to_img_txt(t_cub3d *data, int pixel_x,
	t_dda *wall_config, t_ray *ray)
{
	t_texture	*texture;
	int			tex_x;
	int			displayed_height;
	int			pixel_y_start;
	int			pixel_y_end;
	int			i;
	int			tex_y;
	int			color;

	texture = texture_to_display(data, wall_config->orientation);
	tex_x = get_texture_x(ray, wall_config, texture);
	displayed_height = (int)(SCREEN_HEIGHT / wall_config->dist);
	pixel_y_start = (SCREEN_HEIGHT - displayed_height) / 2;
	pixel_y_end = pixel_y_start + displayed_height;
	i = pixel_y_start;
	while (i < pixel_y_end)
	{
		tex_y = ((i - pixel_y_start) * texture->y) / displayed_height;
		color = *((int *)(texture->pixels + tex_y * texture->line_len
					+ tex_x * (texture->bits_per_pixel / 8)));
		put_pixel(&data->framebuffer, pixel_x, i, color);
		i++;
	}
}
