/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:00:13 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/17 15:53:52 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	print_texture_debug(char **text, t_colors colors)
{
	printf("NO = %s\n", text[NORTH]);
	printf("SO = %s\n", text[SOUTH]);
	printf("WE = %s\n", text[WEST]);
	printf("EA = %s\n", text[EAST]);
	printf("F = %d\n", colors.floor_color);
	printf("C = %d\n", colors.ceiling_color);
}

void	print_map_debug(t_grid *map)
{
	int	i;

	i = 0;
	while (map->grid[i])
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
}
