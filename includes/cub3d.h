#ifndef CUB3D
# define CUB3D

#include "../minilibx-linux/mlx.h"
#include <../libft/libft.h>
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>


# define END_PLAYER "Game succesfully exited by the player\n"

# define E_NB_ARGS "Invalid nuber of arguments: usage: <exe> <map_file>\n"


typedef struct s_screen_rc
{
	double	camerax; //position relative de la ligne par rapport au centre de la camera du joueur (varie entre -1 = gauche 0 = centre et + 1 = droite )
	//double rayangle ? hugo
	double	raydirx; 
	double	raydiry;
	double	planex;
	double	planey;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	int		texnum;
	int		texx;
	double	wallx;
}	t_screen_rc;

//le strict necessaire pour afficher une image
typedef struct s_screen_rc
{
	int		x; //colonne de l' ecran affiche
	//textures (utiliser une structure qui contiendra toutes ces donnees ?)
	double	dist_tex; //distance de la texture a afficher
	int		side; //le cote de la texture a afficher


}	t_screen_rc;

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
	t_screen_rc		raycast;
	t_player		player;
}	t_cub3d;


#endif
