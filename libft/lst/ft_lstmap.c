/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanglade <hanglade@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:31:20 by hanglade          #+#    #+#             */
/*   Updated: 2023/11/09 14:31:20 by hanglade         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_mapped;
	t_list	*begin_mapped;
	void	*tmp;

	lst_mapped = NULL;
	begin_mapped = lst_mapped;
	while (lst)
	{
		tmp = f(lst->content);
		if (!tmp)
		{
			ft_lstclear(&begin_mapped, del);
			return (NULL);
		}
		lst_mapped = ft_lstnew(tmp);
		if (!lst_mapped)
		{
			ft_lstclear(&begin_mapped, del);
			del(tmp);
			return (NULL);
		}
		ft_lstadd_back(&begin_mapped, lst_mapped);
		lst = lst->next;
	}
	return (begin_mapped);
}
