/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 09:44:38 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/24 16:38:20 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_all(char **split, int i, int garbage)
{
	char	*tmp;

	tmp = "";
	while (split[i] && split[i + 1])
	{
		tmp = ft_strjoin(tmp, split[i], garbage);
		tmp = ft_strjoin(tmp, " ", garbage);
		i++;
	}
	tmp = ft_strjoin(tmp, split[i], garbage);
	return (tmp);
}

static void	swap_strs(char **split, char **lower, int i, int j)
{
	char	*tmp;

	if (ft_strcmp(lower[i], lower[j]) > 0)
	{
		tmp = split[i];
		split[i] = split[j];
		split[j] = tmp;
		tmp = lower[i];
		lower[i] = lower[j];
		lower[j] = tmp;
	}
}

char	*ft_sort_strarr(char *arg, int garbage)
{
	int		i;
	int		j;
	char	**lower;
	char	**split;

	split = ft_split(arg, " ", garbage);
	lower = malloc((ft_strarr_size(split) + 1) * sizeof(char *));
	if (!split || !lower)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		lower[i] = ft_strmap(split[i], ft_tolower, garbage);
		if (!lower[i])
			return (NULL);
	}
	i = -1;
	while (split[++i])
	{
		j = i;
		while (split[++j])
			swap_strs(split, lower, i, j);
	}
	return (join_all(split, 0, garbage));
}
