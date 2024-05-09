/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:56:01 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 22:14:46 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_structure(t_cub3d *prog)
{
	int	i;

	i = -1;
	prog->file_to_strs = NULL;
	prog->wall_textures = (t_wall_textures)
	{
		.cardinals_array = {"NO ", "SO ", "WE ", "EA ", "F ", "C "},
		.textures_paths = {NULL, NULL, NULL, NULL, NULL, NULL}
	};
	while (++i < 8)
	{
		if (i < 5)
			prog->sprites[i].reference = NULL;
		prog->torch_sprites[i].reference = NULL;
	}
	prog->raycast_img.img = NULL;
	prog->map_struct.map_strs = NULL;
	prog->map_struct.height = 0;
	prog->map_struct.width = 0;
}

void	global_parsing(t_cub3d *prog, char *file_name)
{
	init_structure(prog);
	if (!is_valid_extension_path(file_name, ".cub") || !file_exist(file_name))
		error_message_and_exit(1, FD_CUB_MSG);
	split_file_string(prog, file_name);
	parse_wall_textures(prog);
	if (!are_all_instructions_present(prog->wall_textures)
		|| !textures_paths_are_correct(*prog))
		error_message_and_exit(1, FD_XPM_MSG);
	if (!are_color_instruction_valid(&prog->wall_textures))
		error_message_and_exit(1, COLOR_FORMAT_ERROR);
	parse_map(prog);
	if (!is_valid_map(prog->map_struct))
		error_message_and_exit(1, INCORECT_MAP_MSG);
	find_player_data(&prog->map_struct, &prog->player);
	alloc_doors(prog, prog->map_struct);
	init_doors(prog, prog->map_struct);
	del_garbage(LOOP);
	prog->colors.sky = get_trgb(0,
			prog->wall_textures.colors[1].octet[0],
			prog->wall_textures.colors[1].octet[1],
			prog->wall_textures.colors[1].octet[2]);
	prog->colors.floor = get_trgb(0,
			prog->wall_textures.colors[0].octet[0],
			prog->wall_textures.colors[0].octet[1],
			prog->wall_textures.colors[0].octet[2]);
}
