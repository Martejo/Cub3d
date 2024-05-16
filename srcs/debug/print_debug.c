#include "../../includes/cub3d.h"


void	print_texture_debug(t_text *text)
{
	printf("NO = %s\n", text->north_texture);
	printf("SO = %s\n", text->south_texture);
	printf("WE = %s\n", text->west_texture);
	printf("EA = %s\n", text->east_texture);
	printf("F = %d\n", text->floor_color);
	printf("C = %d\n", text->ceiling_color);

}

void	print_map_debug(t_map *map)
{
	int	i;

	i = 0;
	while (map->grid[i])
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
}