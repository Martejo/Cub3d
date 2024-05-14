/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 14:16:14 by cberganz          #+#    #+#             */
/*   Updated: 2024/05/14 10:08:38 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <ctype.h>
# include <stdbool.h>
# include <stdio.h>
# include "../libft/include/libft.h"
# include "../mlx-linux/mlx.h"

# define M_PI 3.14159265358979323846

/*
** print color
*/

# define RED     "\x1b[31;1m"
# define RESET   "\x1b[0m"

/*
** Game screen settings
*/

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800
# define TEXT_WIDTH 64 
# define TEXT_HEIGHT 64
/*
** Game settings
*/

# ifndef BONUS_FLAG
#  define BONUS_FLAG 0
# endif

# define CAMERA_SPEED 0.02
# define MOVE_SPEED 0.05
# define ROTATION_ANGLE 1.5
# define HITBOX_SIZE 0.2

/*
** Minimap settings
*/

# define PIXEL_PER_CUBE 10
# define CUBE_PER_LINE 20
# define SIZE_AROUND_PLAYER 10
# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_CENTER 100
# define DIRECTION_LINE_SIZE 10
# define DIRECTION_LINE_WIDTH 1.5
# define MINIMAP_FLOOR_COLOR 0xDE9151
# define MINIMAP_PLAYER_COLOR 0xBB0A21
# define MINIMAP_WALL_COLOR 0x6E7E85
# define MINIMAP_OUTMAP_COLOR 0x001A23

/*
** Raycast settings
*/

# define SIDE1_COLOR 0x0000FF
# define SIDE2_COLOR 0x00FF00

/*
** Keyboard keys
*/

# define D 100
# define A 97
# define W 119
# define S 115
# define RIGHT 65363
# define LEFT 65361
# define TOP 65362
# define BOTTOM 65364
# define ESC 65307
# define CTRL 65507
# define SPACE 32
# define PLUS 61
# define MINUS 45

/*
** Garbage Collector
*/
# define MAIN 0
# define LOOP 1

/*
** Error Messages
*/
# define FD_CUB_MSG "You should pass an existing file with '.cub' extension"
# define FD_XPM_MSG "You should pass an existing texture with .xpm extension"
# define COLOR_FORMAT_ERROR "Invalid color format"
# define TEXTURES_INSTRUCTION_ERROR "Invalid textures instructions"
# define INCORECT_MAP_MSG "Map is incorrect"
# define MALLOC_ERR_MSG "Malloc error"
# define FD_ARG_ERR_MSG "Failed opening argument file"

/*
** Game data structures
*/

typedef struct s_tex
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_length;
	int			endian;
}	t_tex;

typedef struct s_keyboard
{
	uint8_t	left;
	uint8_t	right;
	uint8_t	top;
	uint8_t	bottom;
	uint8_t	right_rotate;
	uint8_t	left_rotate;
}	t_keyboard;

typedef struct s_colors
{
	int			sky;
	int			floor;
}	t_colors;

typedef struct s_player
{
	char	start_dir; // le symbole permettant de definir la direction initiale des vecteurs representant le regard du joueur (par rapport au repere orthonorme informatique) N => dirx = 0 diry = -1 ? S => dirx 0 diry 1 
	//la position du joueur sur la map2d
	double	posx; 
	double	posy;

	// on connait l'angle initial du regard du joueur gr^ace a la lettre N = -Pi/2 
	//si le regard devie, on a juste a faire varier la valeur de l'angle de vue
	//la valeur d' angle augmente quand on tourne le regard `a droite et decroit quand on le tourne `a gauche 
	//attention quand on fait un tour complet dans un sens ou dans l' autre il faut reinitialiser les valeurs d' angle (on 360 + droite = 0)
	
	//int angle; //valeur d' angle entre 0 et 360
	double	dirx; // on l'obtient ewn faisant cos(notre angle)
	double	diry; // on l' obtient en faisant sin(notre angle)
}	t_player;

typedef struct s_image {
	void			*reference;
	int				x;
	int				y;
	unsigned char	*pixels;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}				t_image;

typedef struct s_raycast
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
}	t_raycast;

typedef struct s_color
{
	int	octet[3];
}	t_color;

typedef struct s_wall_textures
{
	char		cardinals_array[6][4];
	char		*textures_paths[6];
	t_color		colors[2];
}	t_wall_textures;

typedef struct s_map
{
	unsigned int		width;
	unsigned int		height;
	char				**map_strs;
}	t_map;

typedef struct s_door
{
	int					increment_step;
	unsigned int		x;
	unsigned int		y;
	unsigned int		step_percent;
}	t_door;

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

/*
** Initialization functions
*/

void	img_initialize(t_cub3d *cub3d, t_tex *minimap_img,
			int width, int height);
void	window_initialize(t_cub3d *cub3d);
void	game_initialize(t_cub3d *cub3d);

/*
** Game functions
*/

void	game_loop(t_cub3d *cub3d);
void	mouse_rotation(t_cub3d *cub3d);
void	set_mouse(t_cub3d *cub3d);
void	raycast(t_cub3d *cub3d, t_raycast *raycast);
t_door	*targeted_door(t_cub3d *cub3d);
void	insert_torch(t_cub3d *cub3d);
void	insert_flame(t_cub3d *cub3d);
void	put_pixel_to_img(t_tex *img, int x, int y, int color);
void	raycast_find_wall(t_cub3d *cub3d, t_raycast *raycast, int do_hit_door);
void	raycast_initialize(t_cub3d *cub3d, t_raycast *raycast, int x);
void	find_texture_index(t_cub3d *cub3d);
void	texture_calculation(t_cub3d *cub3d);
uint8_t	hitbox_wallhit(t_cub3d *cub3d, double x, double y);
uint8_t	is_on_door(t_cub3d *cub3d, t_door *targeted_door);
int		key_press_hook(int key, t_cub3d *cub3d);
int		key_release_hook(int key, t_cub3d *cub3d);
void	move_vision(t_cub3d *cub3d, t_player *player);
void	move_player(t_cub3d *cub3d, t_player *player);
float	get_open_percentage(t_cub3d *cub3d);

/*
** Minimap and overlay functions
*/

void	draw_minimap(t_cub3d *cub3d);

/*
**	PARSING ROBIN
*/
void	split_file_string(t_cub3d *prog, char *file_name);
bool	parse_wall_textures(t_cub3d *prog);
bool	is_space_line(char *str);
void	parse_map(t_cub3d *prog);
void	global_parsing(t_cub3d *prog, char *file_name);
void	find_player_data(t_map *map, t_player *player);
t_image	ft_new_sprite(t_cub3d *prgm, char *path);
void	init_sprites(t_cub3d *prgm);
void	init_doors(t_cub3d *cub3d, t_map map);
void	alloc_doors(t_cub3d *cub3d, t_map map);
bool	extrem_lines_are_correct(char *line);

/*
**	CHECK ERRORS ROBIN
*/
bool	textures_paths_are_correct(t_cub3d prog);
bool	is_valid_extension_path(char *path, char *extension);
bool	file_exist(char *path);
bool	are_all_instructions_present(t_wall_textures textures);
bool	are_color_instruction_valid(t_wall_textures *textures);
bool	is_valid_map(t_map map);

/*
**	UTILS ROBIN
*/
void	free_and_exit(int exit_code);
bool	is_int_overflow(char *str_nbr);
bool	is_str_digit(char *str);
void	error_message_and_exit(int exit_code, char *message);
void	find_pix(t_cub3d *cub, int y, unsigned char **pix, t_image *sprite);

/*
** Tools functions
*/

int		get_trgb(int t, int r, int g, int b);
float	get_distance(float x1, float y1, float x2, float y2);

/*
** Exit functions
*/

void	exit_game(t_cub3d *cub3d, char *msg, int exit_status);
int		exit_button(t_cub3d *cub3d);

#endif