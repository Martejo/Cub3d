#ifndef CUB3D
# define CUB3D

#include "../minilibx-linux/mlx.h"
#include <../libft/libft.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


# define E_NB_ARGS "Invalid nuber of arguments: usage: <exe> <map_file>\n"

typedef struct s_cub3d
{
	void			*mlx;
	void			*mlx_win;
	char			**map;
	int				height;
	int				width;
	float			move_speed;
	float			camera_speed;
	char			**file_to_strs;
	t_wall_textures	wall_textures;
	t_image			sprites[5];
	t_image			torch_sprites[8];
	t_map			map_struct;
	int				doors_nbr;
	t_door			*doors;
	uint8_t			mouse_set;
	t_tex			raycast_img;
	t_colors		colors;
	t_keyboard		keyboard;
	t_raycast		raycast;
	t_player		player;
}	t_cub3d;


#endif
