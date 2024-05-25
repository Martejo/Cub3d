#include "../../../includes/cub3d.h"

int	key_press_hook(int key, t_cub3d *data)
{
	if (key == XK_w)
		data->key.key_w = 1;
	else if (key == XK_s)
		data->key.key_s = 1;
	else if (key == XK_a)
		data->key.key_a = 1;
	else if (key == XK_d)
		data->key.key_d = 1;
	else if (key == XK_Left)
		data->key.key_left = 1;
	else if (key == XK_Right)
		data->key.key_right = 1;
	else if (key == XK_Escape)
		close_programm(data, "Close program", EXIT_SUCCESS);
	return (0);
}

int	key_release_hook(int key, t_cub3d *data)
{
	if (key == XK_w)
		data->key.key_w = 0;
	else if (key == XK_s)
		data->key.key_s = 0;
	else if (key == XK_a)
		data->key.key_a = 0;
	else if (key == XK_d)
		data->key.key_d = 0;
	else if (key == XK_Left)
		data->key.key_left = 0;
	else if (key == XK_Right)
		data->key.key_right = 0;
	return (0);
}

int	exit_button(t_cub3d *cub3d)
{
	close_programm(cub3d, "Game exited by user.", EXIT_SUCCESS);
	return (0);
}
