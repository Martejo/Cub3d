/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:18:21 by cberganz          #+#    #+#             */
/*   Updated: 2022/06/05 22:15:40 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **envp)
{
	t_cub3d	cub3d;

	if (argc != 2)
	{
		printf("Error\nInvalid nuber of arguments.\nUsage <exe> <map_file>\n");
		return (0);
	}
	if (!envp)
		return (0);
	global_parsing(&cub3d, argv[1]);
	window_initialize(&cub3d);
	init_sprites(&cub3d);
	img_initialize(&cub3d, &cub3d.raycast_img, SCREEN_WIDTH, SCREEN_WIDTH);
	game_initialize(&cub3d);
	game_loop(&cub3d);
	return (0);
}
