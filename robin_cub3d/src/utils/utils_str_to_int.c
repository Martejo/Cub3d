/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str_to_int.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 20:13:00 by rbicanic          #+#    #+#             */
/*   Updated: 2022/06/05 20:13:39 by rbicanic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_int_overflow(char *str_nbr)
{
	int		sign;
	size_t	str_len;

	str_len = ft_strlen(str_nbr);
	if (str_nbr[0] == '-')
		sign = -1;
	else
		sign = 1;
	if ((sign < 0 && str_len > 11) || (sign > 0 && str_len > 10))
		return (true);
	else if ((sign < 0 && str_len < 11) || (sign > 0 && str_len < 10))
		return (false);
	if ((sign < 0 && ft_strcmp(str_nbr, "-2147483648") > 0)
		|| (sign > 0 && ft_strcmp(str_nbr, "2147483647") > 0))
		return (true);
	return (false);
}

bool	is_str_digit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}
