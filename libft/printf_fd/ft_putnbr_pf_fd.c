/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:23:38 by gemartel          #+#    #+#             */
/*   Updated: 2024/03/08 15:23:41 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_pf_fd(int fd, int nbr, size_t *count_char)
{
	if (nbr == -2147483648)
	{
		ft_putstr_pf_fd(fd, "-2147483648", count_char);
		return ;
	}
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar_pf_fd(fd, '-', count_char);
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar_pf_fd(fd, nbr + 48, count_char);
	}
	else
	{
		ft_putnbr_pf_fd(fd, nbr / 10, count_char);
		ft_putnbr_pf_fd(fd, nbr % 10, count_char);
	}
}

void	ft_putnbr_unsigned_fd(int fd, unsigned int nbr, size_t *count_char)
{
	if (nbr > 9)
	{
		ft_putnbr_unsigned_fd(fd, nbr / 10, count_char);
		ft_putnbr_unsigned_fd(fd, nbr % 10, count_char);
	}
	else
		ft_putchar_pf_fd(fd, nbr + 48, count_char);
}
