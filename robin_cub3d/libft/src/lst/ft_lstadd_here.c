/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_here.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cberganz <cberganz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 12:03:51 by cberganz          #+#    #+#             */
/*   Updated: 2022/02/20 13:39:33 by cberganz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_here(t_list *alst, t_list *new)
{
	t_list		*tmp;

	if (alst != NULL)
	{
		tmp = alst->next;
		alst->next = new;
		new->next = tmp;
	}
}
