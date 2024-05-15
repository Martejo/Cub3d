#include "../../includes/cub3d.h"

void	print_and_exit_error(char *msg)
{
	ft_printf_fd(2, "%s%s%s\n", RED, msg, RESET);
	exit(EXIT_FAILURE);
}

void	free_and_exit_error(char *msg)
{
	ft_printf_fd(2, "%s%s%s\n", RED, msg, RESET);
	clear_garbage(ARRAY, free);
	clear_garbage(TMP, free);
	clear_garbage(STRUCT, free);
	exit(EXIT_FAILURE);
}