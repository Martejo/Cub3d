/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:32:00 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:32:00 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_lstsize(t_list *lst)
{
	int		len;
	t_list	*tmp;

	len = 0;
	tmp = lst;
	if (tmp == NULL)
		return (0);
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
