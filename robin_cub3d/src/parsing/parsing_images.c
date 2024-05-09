/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_images.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 18:27:17 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 16:42:56 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_image	ft_new_sprite(t_cub3d *prgm, char *path)
{
	t_image	img;

	img.reference = mlx_xpm_file_to_image(prgm->mlx, path, &img.x,
			&img.y);
	if (img.reference == NULL)
	{
		exit_game(prgm, "Error\nImpossible sprite conversion to image\n", 1);
	}
	img.pixels = (unsigned char *)mlx_get_data_addr(img.reference,
			&img.bits_per_pixel, &img.line_len, &img.endian);
	return (img);
}

void	init_sprites(t_cub3d *prgm)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		prgm->sprites[i] = ft_new_sprite(prgm,
				prgm->wall_textures.textures_paths[i]);
		i++;
	}
	if (!file_exist("sprites/door.xpm"))
		exit_game(prgm, FD_XPM_MSG, 1);
	if (prgm->doors_nbr && BONUS_FLAG)
		prgm->sprites[4] = ft_new_sprite(prgm, "sprites/door.xpm");
}
