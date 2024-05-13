
#include "../includes/cub3d.h"

int	main(int ac, char **av, char **envp)
{
	t_cub3d	cub3d;
	if (argc != 2)
		exit_err(E_NB_ARGS);
	if (!envp)//a quoi sert cette verif ?
		return (0);
	manage_parsing(&cub3d, argv[1]);
	init_mlx(&cub3d);
	


}
