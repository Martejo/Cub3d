#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include "../libft/libft.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

/*
** Define size window
*/
# ifndef SCREEN_HEIGHT
#  define SCREEN_HEIGHT 800
# endif 
# ifndef SCREEN_WIDTH
#  define SCREEN_WIDTH 800
# endif 

/*
** Define grid limits
*/
# define MAX_HEIGHT 1000
# define MAX_WIDHT 1000

/*
**Color Definition**
*/

# define RED     "\x1b[31;1m"
# define GREEN   "\x1b[32m"
# define YELLOW  "\x1b[33m"
# define BLUE    "\x1b[34m"
# define MAGENTA "\x1b[35m"
# define CYAN    "\x1b[36m"
# define RESET   "\x1b[0m"

/*
**Message Definition**
*/

# define E_NB_ARGS "Invalid number of arguments: usage: <exe> <map_file>\n"
# define E_PREPROCESS_MACRO "Invalid values for preprocess macros\n"
# define FILE_EXTENSION "Error\nWrong file extension. Cub3d need <*.cub>\n"
# define FILE_PATH "Error\nCannot open file.\n"
# define SYNTAX_LINE "Error\nInvalid syntax in configuration.\n"
# define TEXT_PATH "Error\nInvalid path for texture.\n"
# define COLOR_FORMAT_ERROR "Error\nInvalid color format.\n"
# define WRONG_CHR "Error\nInvalid character in map.\n"
# define MAP_ERROR "Error\nInvalid map format\n"
# define EMPTY_START "Error\nNo starting position in map.\n"
# define MULT_START "Error\nMultiple starting positions in map.\n"
# define MALLOC_ERR_MSG "Malloc error\n"
# define SIZE_ERROR_GRID "Error\nMax size grid -> 100*100\n"
# define MLX_IMG_ERROR "Error\nMLX image creation failed\n"
# define MLX_PTR_ERROR "Error\nMLX pointer creation failed\n"
# define MLX_SPRITE_ERROR "Error\nMLX xpm image creation failed\n"

/*
**Game Macro Definition
*/
// # ifndef FOV
// #  define FOV 66
// # endif
// # define FOV_RAD (FOV * PI / 180)
// # define PLANE_FOV tan(FOV_RAD / 2)
# ifndef PLANE_FOV
#  define PLANE_FOV 0.649408
# endif
# ifndef PLAYER_STEP_SIZE
#  define PLAYER_STEP_SIZE 0.050
# endif
# ifndef PLAYER_ROT_SPEED
#  define PLAYER_ROT_SPEED 0.032
# endif
# define PI 3.1415926535
/*
**Enum Definition
*/

enum e_texture_index
{
	NORTH = 0,
	SOUTH = 1,
	EAST = 2,
	WEST = 3,
	F,
	C
};

enum e_id_gc
{
	STRUCT = 0,
	TEXTURE,
	GRID,
	MLX,
	TMP
};

/*
**Structure Definition
*/

typedef struct s_key_handl
{
	int	w;
	int	s;
	int	a;
	int	d;
	int	left;
	int	right;

}	t_key_handl;

typedef struct s_fvector
{
	float	x;
	float	y;
}	t_fvector;

typedef struct s_dvector
{
	double	x;
	double	y;
}	t_dvector;

typedef struct s_ivector
{
	int	x;
	int	y;
}	t_ivector;

typedef struct s_player
{
	double		dir_angle;
	t_dvector	pos;
	t_dvector	dir;
	t_dvector	plane;
	t_dvector	movement;
}	t_player;

typedef struct t_dda
{
	double	dist;
	char	orientation;
}	t_dda;

typedef struct s_ray
{
	t_ivector	grid_pos;
	t_ivector	step_direction;
	t_dvector	true_pos;
	t_dvector	dir;
	t_dvector	delta_dist;
	t_dvector	side_dist;
}	t_ray;

typedef struct s_raycast
{
	double	camera_x;
	double	perp_wall_dist;
	t_ray	ray;
}	t_raycast;

typedef struct s_colors
{
	int	floor_color;
	int	ceiling_color;
}	t_colors;

typedef struct s_grid
{
	char	**content;
	int		width;
	int		height;
}	t_grid;

typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_pixel_column
{
	int		tex_x;
	int		tex_y;
	int		y_start;
	int		y_end;
	int		height;
	int		color;
}	t_pixel_column;

typedef struct s_texture
{
	void			*reference;
	unsigned char	*pixels;
	int				x;
	int				y;
	int				bits_per_pixel;
	int				line_len;
	int				endian;
}	t_texture;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		width;
	int		height;
}	t_mlx;

typedef struct s_cub3d
{
	t_mlx		mlx;
	t_grid		grid;
	t_player	player;
	char		**text_path;
	t_texture	text_img[4];
	t_colors	colors;
	t_image		framebuffer;
	t_key_handl	key;
}	t_cub3d;

/*
**Functions Definition
*/

/**Error_handling**/
void	print_and_exit_error(char *msg);
void	free_and_exit_error(char *msg);
void	close_programm(t_cub3d *cub3d, char *msg, int exit_code);

/**Init_structure**/
t_cub3d	*init_struct(void);
void	init_mlx(t_mlx *mlx);
void	init_image(t_cub3d *data);
void	init_sprites(t_cub3d *data);

/**Parsing handler**/
void	process_config_and_map(t_cub3d *data, char *file);

/***Parsing_map***/
void	extract_grid(t_grid *grid, char **grid_in_file);

/***Parsing map utils***/
bool	is_space_line(char *str);
int		get_height_grid(char **grid);
int		get_max_width_grid(char **grid);
bool	is_char_adjacent_to_space(char **map, int x, int y);

/***Parsing_texture***/
void	extract_texture_path(char ***texture, char *line, int index_text);
int		get_texture_index_from_line(char *line);

/***Parsing file***/
char	**extract_file(char *file);
void	test_and_open_file(char *file);

/***Parsing colors***/
void	extract_color(t_colors *colors, char *line, int index_color);

/**Debug**/
void	print_texture_debug(char **text, t_colors colors);
void	print_map_debug(t_grid *map);

/**Game_loop**/
void	create_raycast_img(t_cub3d *data);
void	game_event_loop(t_cub3d *data);

/**Controller/Key_management**/
int		key_press_hook(int key, t_cub3d *data);
int		key_release_hook(int key, t_cub3d *data);
int		exit_button(t_cub3d *cub3d);

/**Frame/print_frame**/
void	draw_floor_ceil(t_cub3d *data, t_image *img);
void	put_pixel(t_image *img, int col, int line, int color);
void	add_pixels_col_to_img_txt(t_cub3d *data, int pixel_x,
			t_dda *wall_config, t_ray *ray);

/**Player**/
void	init_player(t_grid *grid, t_player *player);
int		modif_player(t_cub3d *data);
bool	is_player(char c);
double	to_rad(int degrees);
void	process_player_movement(t_player *player);
void	process_player_dir(t_player *player);
void	process_player_plane(t_player *player);

/**Ray-casting/DDA**/
void	get_ray_config_dda(t_ray *ray);
void	init_ray(const double camera_x, t_player *player, t_ray *ray);
void	get_wall_config_dda(const t_grid *grid, t_ray *ray, t_dda *wall_config);

#endif
