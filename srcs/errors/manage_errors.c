#include "../includes/cub3d.h"

void	exit_error(t_cub3d *c3d, char *err)
{
	ft_putstr_fd(err, 2);
	clean_prog(c3d);
	exit(EXIT_FAILURE);
}