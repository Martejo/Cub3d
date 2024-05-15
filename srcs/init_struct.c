#include "../includes/cub3d.h"


t_cub3d	*init_struct(void)
{
	t_cub3d *data;

	data = calloc_gc(1, sizeof(t_cub3d), STRUCT);
	if (!data)
		print_and_exit_error(MALLOC_ERR_MSG);
	return (data);
}