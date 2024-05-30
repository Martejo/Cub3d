/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 14:00:09 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/28 14:00:12 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	args_check(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		print_and_exit_error(E_NB_ARGS);
	if (SCREEN_HEIGHT > 1800 || SCREEN_WIDTH > 3200
		|| PLANE_FOV < 0.6 || PLANE_FOV > 1.4
		|| PLAYER_ROT_SPEED > 0.1 || PLAYER_STEP_SIZE > 0.2)
		print_and_exit_error(E_PREPROCESS_MACRO);
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
	init_sprites(data);
	init_player(&data->grid, &data->player);
	game_event_loop(data);
	return (0);
}
