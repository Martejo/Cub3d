/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:00:13 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/23 14:41:29 by hanglade         ###   ########.fr       */
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

void	print_map_debug(t_grid *grid)
{
	int	i;

	i = 0;
	printf("height = %d\nmax_width = %d\n", grid->height, grid->width);
	while (grid->content[i])
	{
		printf("%s\n", grid->content[i]);
		i++;
	}
}
