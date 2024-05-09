/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:30:38 by cberganz          #+#    #+#             */
/*   Updated: 2021/11/25 16:31:18 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	nrecu;

	if (n < 0)
		ft_putchar_fd('-', fd);
	nrecu = ft_abs(n);
	if (nrecu >= 10)
	{
		ft_putnbr_fd(nrecu / 10, fd);
		ft_putchar_fd(nrecu % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nrecu + '0', fd);
}
