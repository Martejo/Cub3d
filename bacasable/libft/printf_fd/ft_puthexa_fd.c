/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthexa_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:45:58 by gemartel          #+#    #+#             */
/*   Updated: 2024/02/29 10:32:27 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puthexa_upper_fd(int fd, unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_upper_fd(fd, nbr / 16, count_char);
	ft_putchar_pf_fd(fd, "0123456789ABCDEF"[nbr % 16], count_char);
}

void	ft_puthexa_lower_fd(int fd, unsigned int nbr, size_t *count_char)
{
	if (nbr > 15)
		ft_puthexa_lower_fd(fd, nbr / 16, count_char);
	ft_putchar_pf_fd(fd, "0123456789abcdef"[nbr % 16], count_char);
}
