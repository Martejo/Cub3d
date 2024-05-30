/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:30:48 by gemartel          #+#    #+#             */
/*   Updated: 2024/05/30 14:37:33 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_double_text(int index, t_text_file *text)
{
	if ((index == NORTH && text->no == true)
		|| (index == SOUTH && text->so == true)
		|| (index == WEST && text->we == true)
		|| (index == EAST && text->ea == true))
		free_and_exit_error(CONFIG_ERROR);
}

void	save_text_path(t_text_file *text_path, int index, char *path)
{
	if (index == NORTH)
	{
		text_path->text[NORTH] = path;
		text_path->no = true;
	}
	else if (index == SOUTH)
	{
		text_path->text[SOUTH] = path;
		text_path->so = true;
	}
	else if (index == EAST)
	{
		text_path->text[EAST] = path;
		text_path->ea = true;
	}
	else if (index == WEST)
	{
		text_path->text[WEST] = path;
		text_path->we = true;
	}
}
