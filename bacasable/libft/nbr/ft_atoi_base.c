/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:19:50 by hanglade          #+#    #+#             */
/*   Updated: 2024/01/24 10:55:37 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	pos_in_base(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

long long	process_number(const char *nptr, char *base, int size_base)
{
	int			i;
	int			pos;
	long long	nbr;

	i = 0;
	pos = 0;
	nbr = 0;
	while (nptr[i])
	{
		pos = pos_in_base(nptr[i], base);
		if (pos < 0)
			return (nbr);
		nbr *= size_base;
		nbr += pos;
		i++;
	}
	return (nbr);
}

int	ft_atoi_base(const char *nptr, char *base, int size_base)
{
	int			i;
	int			sign;

	i = 0;
	sign = 1;
	if (!nptr || !base || size_base < 2)
		return (0);
	while (nptr[i] == ' ' || (nptr[i] >= 9 && (nptr[i] <= 13)))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	return ((int)(process_number(&nptr[i], base, size_base) * sign));
}
