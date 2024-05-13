/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 10:33:31 by hanglade          #+#    #+#             */
/*   Updated: 2024/02/29 10:33:33 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	print_flag_fd(int fd, va_list args, char *str, size_t *count_char)
{
	if (str[0] == 'c')
		ft_putchar_pf_fd(fd, va_arg(args, int), count_char);
	else if (str[0] == 's')
		ft_putstr_pf_fd(fd, va_arg(args, char *), count_char);
	else if (str[0] == 'p')
		print_ptr_addr_fd(fd, va_arg(args, void *), count_char);
	else if (str[0] == 'd' || str[0] == 'i')
		ft_putnbr_pf_fd(fd, va_arg(args, int), count_char);
	else if (str[0] == 'u')
		ft_putnbr_unsigned_fd(fd, va_arg(args, unsigned int), count_char);
	else if (str[0] == 'x')
		ft_puthexa_lower_fd(fd, va_arg(args, unsigned int ), count_char);
	else if (str[0] == 'X')
		ft_puthexa_upper_fd(fd, va_arg(args, unsigned int), count_char);
	else if (str[0] == '%')
		ft_putchar_pf_fd(fd, '%', count_char);
}

int	ft_printf_fd(int fd, const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	count_char;

	if (!str || fd < 0)
		return (-1);
	if (write(fd, 0, 0) == -1)
		return (-1);
	i = 0;
	count_char = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			print_flag_fd(fd, args, (char *)&str[i], &count_char);
		}
		else
			ft_putchar_pf_fd(fd, str[i], &count_char);
		i++;
	}
	va_end(args);
	return ((int)count_char);
}
