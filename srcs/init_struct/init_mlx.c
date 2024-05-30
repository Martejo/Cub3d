/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 13:57:41 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 13:57:43 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	init_image(t_cub3d *data)
{
	data->framebuffer.img_ptr = mlx_new_image(data->mlx.mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!data->framebuffer.img_ptr)
		free_and_exit_error(MLX_IMG_ERROR);
	data->framebuffer.addr = mlx_get_data_addr(data->framebuffer.img_ptr,
			&data->framebuffer.bpp, &data->framebuffer.line_len,
			&data->framebuffer.endian);
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		free_and_exit_error(MLX_PTR_ERROR);
	add_to_garbage(mlx->mlx_ptr, MLX);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3d");
}
