/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar2_endl.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:47:56 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/15 18:56:49 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putchar2_endl(char **char2)
{
	size_t	i;

	i = 0;
	while (char2[i])
	{
		ft_putstr_fd(char2[i], 1);
		write(1, "\n", 1);
		i++;
	}
}
