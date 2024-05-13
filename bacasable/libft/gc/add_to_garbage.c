/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_garbage.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:32:20 by hanglade          #+#    #+#             */
/*   Updated: 2024/03/08 15:21:34 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*add_to_garbage(void *ptr, int id_gc)
{
	t_list	*el;

	if (id_gc < 0 || id_gc >= GARBAGE_SIZE)
		return (NULL);
	el = ft_lstnew(ptr);
	if (el == NULL)
		return (free(ptr), NULL);
	ft_lstadd_front(garbage_ptr(id_gc), el);
	return (ptr);
}
