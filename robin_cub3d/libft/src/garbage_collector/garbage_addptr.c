/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_addptr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbicanic <rbicanic@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 12:24:27 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/02 22:55:11 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*garbage_addptr(void *ptr, int id)
{
	t_list	*el[10];

	el[id] = garbage_lstnew(ptr);
	if (el[id] == NULL)
		return (NULL);
	ft_lstadd_front(garbage(id), el[id]);
	return (ptr);
}
