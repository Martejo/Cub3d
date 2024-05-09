/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:57:36 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/18 16:41:02 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_double_checker(char *base, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (base[i])
	{
		if (base[i] == c)
		{
			count++;
			if (count == 2)
				return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_base_work(char *base, unsigned int *base_count)
{
	while (base[*base_count])
	{
		if (base[*base_count] == '+' || base[*base_count] == '-'
			|| ft_double_checker(base, base[*base_count]))
			return (0);
		*base_count += 1;
	}
	if (*base_count <= 1)
		return (0);
	else
		return (1);
}

static void	ft_recu(char *base, unsigned int nbr, unsigned int base_count)
{
	if (nbr >= base_count)
	{
		ft_recu(base, nbr / base_count, base_count);
		ft_putchar_fd(base[nbr % base_count], 1);
	}
	else
		ft_putchar_fd(base[nbr], 1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	unsigned int	base_count;

	base_count = 0;
	if (ft_base_work(base, &base_count))
	{
		if (nbr < 0)
		{
			ft_putchar_fd('-', 1);
			nbr *= -1;
		}
		ft_recu(base, (unsigned int) nbr, base_count);
	}
}
