/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_gc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:12:31 by hanglade          #+#    #+#             */
/*   Updated: 2024/03/08 15:22:00 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap_gc(t_list *lst, void *(*f)(void *), void (*del)(void *),
	int id_gc)
{
	t_list	*nlst;
	t_list	*elem;

	if (!lst || !f)
		return (NULL);
	nlst = NULL;
	while (lst)
	{
		elem = ft_lstnew_gc(f(lst->content), id_gc);
		if (!elem)
		{
			clear_garbage(id_gc, del);
			return (NULL);
		}
		ft_lstadd_back(&nlst, elem);
		lst = lst->next;
	}
	return (nlst);
}
