


#include "../minilibx-linux/mlx.h"

int	main(int ac, char **av)
{
	t_cub3d	cub3d;
	if (argc != 2)
		exit_err(E_NB_ARGS);
	manage_parsing(&cub3d, argv[1]);

}
