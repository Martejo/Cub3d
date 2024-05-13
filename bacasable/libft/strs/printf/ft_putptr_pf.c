/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:46:24 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/07 15:15:55 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_ptr_addr(void *ptr, size_t *count_char)
{
	unsigned long	addr;
	char			addr_str[16];
	int				i;

	if (!ptr)
	{
		ft_putstr_pf("(nil)", count_char);
		return ;
	}
	addr = (unsigned long)ptr;
	ft_putstr_pf("0x", count_char);
	i = 0;
	while (addr)
	{
		addr_str[i++] = "0123456789abcdef"[addr % 16];
		addr = addr / 16;
	}
	while (i > 0)
		ft_putchar_pf(addr_str[--i], count_char);
}
