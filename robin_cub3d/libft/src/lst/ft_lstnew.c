/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 13:28:01 by cberganz          #+#    #+#             */
/*   Updated: 2022/03/03 10:19:35 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content, int garbage)
{
	t_list	*nlst;

	if (mem_alloc(sizeof(*nlst), (void **)&nlst, garbage))
		return (NULL);
	nlst->content = content;
	nlst->next = NULL;
	return (nlst);
}
