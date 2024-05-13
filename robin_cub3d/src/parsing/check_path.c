/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 22:29:21 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/06 15:27:43 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	file_exist(char *path)
{
	char	c;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	if (read(fd, &c, 1) == -1)
		return (false);
	close(fd);
	return (true);
}

bool	is_valid_extension_path(char *path, char *extension)
{
	int		path_len;

	path_len = ft_strlen(path);
	// printf("path = '%s'", path);//debug hugo
	if (path_len < 5) //check if file name contains 1 letter min (plus extension)
		return (false);
	if (ft_strcmp(extension, &path[path_len - (ft_strlen(extension))]))
		return (false);
	return (true);
}

//hugo version
//la taille de l' extension n' est pas hard codee a 3
bool	is_valid_extension_path_hugo(char *path, char *extension)
{
	size_t		path_len;
	size_t		ext_len;

	path_len = ft_strlen(path);
	ext_len = ft_strlen(extension);
	// printf("path = '%s'", path);//debug hugo
	if (path_len - ext_len < 1)
		return (false);
	if (ft_strcmp(extension, &path[path_len - ext_len]))
		return (false);
	return (true);
}

bool	textures_paths_are_correct(t_cub3d prog)
{
	int				i;
	t_wall_textures	wall_text;

	i = 0;
	wall_text = prog.wall_textures;
	while (i < 4)
	{
		if (!is_valid_extension_path(wall_text.textures_paths[i], ".xpm" )
			|| !file_exist(wall_text.textures_paths[i]))
			return (false);
		i++;
	}
	return (true);
}
