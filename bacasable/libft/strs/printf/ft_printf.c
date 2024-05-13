/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:45:34 by gemartel          #+#    #+#             */
/*   Updated: 2023/12/07 15:15:34 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_flag(va_list args, char *str, size_t *count_char)
{
	if (str[0] == 'c')
		ft_putchar_pf(va_arg(args, int), count_char);
	else if (str[0] == 's')
		ft_putstr_pf(va_arg(args, char *), count_char);
	else if (str[0] == 'p')
		print_ptr_addr(va_arg(args, void *), count_char);
	else if (str[0] == 'd' || str[0] == 'i')
		ft_putnbr_pf(va_arg(args, int), count_char);
	else if (str[0] == 'u')
		ft_putnbr_unsigned(va_arg(args, unsigned int), count_char);
	else if (str[0] == 'x')
		ft_puthexa_lower(va_arg(args, unsigned int ), count_char);
	else if (str[0] == 'X')
		ft_puthexa_upper(va_arg(args, unsigned int), count_char);
	else if (str[0] == '%')
		ft_putchar_pf('%', count_char);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	count_char;

	if (!str)
		return (-1);
	if (write(1, 0, 0) == -1)
		return (-1);
	i = 0;
	count_char = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_flag(args, (char *)&str[i], &count_char);
		}
		else
			ft_putchar_pf(str[i], &count_char);
		i++;
	}
	va_end(args);
	return ((int)count_char);
}
