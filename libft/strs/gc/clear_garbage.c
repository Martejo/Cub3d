/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_garbage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gemartel <gemartel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 14:27:13 by hanglade          #+#    #+#             */
/*   Updated: 2024/03/08 15:19:59 by gemartel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	clear_garbage(int id_gc, void (*del)(void*))
{
	ft_lstclear(garbage_ptr(id_gc), del);
}
