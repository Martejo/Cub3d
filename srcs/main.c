
#include "../includes/cub3d.h"

void	args_check(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		print_and_exit_error(E_NB_ARGS);
	i = ft_strlen(argv[1]) - 4;
	if (ft_strcmp(&argv[1][i], ".cub") != 0)
		print_and_exit_error(FILE_EXTENSION);
}

int	main(int argc, char **argv)
{
	t_cub3d	*data;

	args_check(argc, argv);
	data = init_struct();
	parsing_handler(data, argv[1]);
	return (0);
}
