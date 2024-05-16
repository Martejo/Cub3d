#ifndef CUB3D_H
# define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include <math.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

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

# define E_NB_ARGS "Invalid nuber of arguments: usage: <exe> <map_file>\n"
# define FILE_EXTENSION "Error\nWrong file extension. Cub3d need <*.cub>\n"
# define FILE_PATH "Error\nCannot open map file.\n"
# define SYNTAX_LINE "Error\nInvalid syntax in configuration.\n"
# define TEXT_PATH "Error\nInvalid path for texture.\n"
# define COLOR_FORMAT_ERROR "Error\nInvalid color format.\n"
# define WRONG_CHR "Error\nInvalid character in map.\n"
# define MAP_ERROR "Error\nInvalid map format\n"
# define EMPTY_START "Error\nNo starting position in map.\n"
# define MULT_START "Error\nMultiple starting positions in map.\n"
# define MALLOC_ERR_MSG "Malloc error\n"



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
	ARRAY,
	MLX,
	TMP
};

/*
**Structure Definition
*/

// Structure player

//Structure ray

typedef struct s_text
{
	char *north_texture;
	char *south_texture;
	char *west_texture;
	char *east_texture;
	int floor_color;
	int ceiling_color;
}	t_text;


typedef struct s_vector
{
	double x;
	double y;
} t_vector;


typedef struct s_map
{
	char **grid;
	int width;
	int height;
}	t_map;

typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
	int addr;
	int size_line;
	int endian;
	int	win_height;
	int	win_width;
}	t_mlx;

typedef struct s_cub3d
{
	t_mlx	mlx;
	t_map	map;
	t_text	text;
}	t_cub3d;

/*
**Functions Definition
*/

/**Error_handling**/
void	print_and_exit_error(char *msg);
void	free_and_exit_error(char *msg);

/**Init_structure**/
t_cub3d	*init_struct(void);

/**Parsing handler**/
void	parsing_handler(t_cub3d *data, char *file);

/***Parsing_map***/
char	**extract_map(char **map);

/***Parsing map utils***/
bool	is_space_line(char *str);
int	get_size_map(char **map);
bool	char_is_next_space(char **map, int x, int y);



/***Parsing_texture***/
void extract_texture_path(t_text *texture, const char *line, int index_text);
int	parse_texture_color(t_cub3d *data, char **file);
int	search_index_texture(char *line);

/***Parsing file***/
char	**extract_file(char *file);
void	test_and_open_file(char *file);

/***Parsing colors***/
void	extract_color(t_text *texture, char *line, int index_color);

/**Debug**/
void	print_texture_debug(t_text *text);
void	print_map_debug(t_map *map);

#endif
