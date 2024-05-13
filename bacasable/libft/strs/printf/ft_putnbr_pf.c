/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:46:10 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/07 15:15:50 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_pf(int nbr, size_t *count_char)
{
	if (nbr == -2147483648)
	{
		ft_putstr_pf("-2147483648", count_char);
		return ;
	}
	if (nbr < 0)
	{
		nbr *= -1;
		ft_putchar_pf('-', count_char);
	}
	if (nbr >= 0 && nbr <= 9)
	{
		ft_putchar_pf(nbr + 48, count_char);
	}
	else
	{
		ft_putnbr_pf(nbr / 10, count_char);
		ft_putnbr_pf(nbr % 10, count_char);
	}
}

void	ft_putnbr_unsigned(unsigned int nbr, size_t *count_char)
{
	if (nbr > 9)
	{
		ft_putnbr_unsigned(nbr / 10, count_char);
		ft_putnbr_unsigned(nbr % 10, count_char);
	}
	else
		ft_putchar_pf(nbr + 48, count_char);
}
