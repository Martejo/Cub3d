/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:30:36 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:30:36 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	len_itoa(int n)
{
	int	len;

	len = 0;
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	is_negative(int *sign, int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		(*sign)++;
	}
}

char	*ft_itoa(int n)
{
	char	*str_num;
	int		sign;
	int		len;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 0;
	is_negative(&sign, &n);
	len = len_itoa(n);
	str_num = ft_calloc((len + 1) + sign, 1);
	if (str_num == NULL)
		return (NULL);
	if (sign == 0)
		len--;
	while (n > 0)
	{
		str_num[len--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == 1)
		str_num[0] = '-';
	return (str_num);
}
