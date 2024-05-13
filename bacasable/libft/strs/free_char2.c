/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_char2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:48:05 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/15 18:57:19 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	free_char2(char ***a_char2)
{
	size_t	i;
	char	**char2;

	i = 0;
	char2 = *a_char2;
	while (char2[i])
	{
		free(char2[i]);
		char2[i] = NULL;
		i++;
	}
	free(char2);
}
