/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:03:27 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/23 15:43:34 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	args_check(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		print_and_exit_error(E_NB_ARGS);
	i = ft_strlen(argv[1]) - 4;
	if (ft_strcmp(&argv[1][i], ".cub") != 0)
		print_and_exit_error(FILE_EXTENSION);
}

int	main(int argc, char **argv)
{
	t_cub3d	*data;

	args_check(argc, argv);
	data = init_struct();
	process_config_and_map(data, argv[1]);
	init_mlx(&data->mlx);
	init_image(data);
	// init_sprites(data);
	//hugo
	// config_grid(&data->grid);//geof l' a deja fait
	init_player(&data->grid, &data->player);
	game_loop(data);
	print_texture_debug(data->text_path, data->colors);
	print_map_debug(&data->grid);
	close_programm(data, "test", 1);
	//free_and_exit_error("OK\n");
	return (0);
}
