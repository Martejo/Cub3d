#include "../../includes/cub3d.h"

t_texture	new_sprite(t_cub3d *data, int i)
{
	t_texture	sprite;

	sprite.reference = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
			data->text_path[i], &sprite.x, &sprite.y);
	if (!sprite.reference)
		free_and_exit_error(MLX_SPRITE_ERROR);
	sprite.pixels = (unsigned char *)mlx_get_data_addr(sprite.reference,
			&sprite.bits_per_pixel, &sprite.line_len, &sprite.endian);
	return (sprite);
}

void	init_sprites(t_cub3d *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		data->text_img[i] = new_sprite(data, i);
		i++;
	}
}
