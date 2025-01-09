/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_lst_2node.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 12:03:55 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:25:12 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_del_lst_2node(t_list_2 **node, void (*del)(void *))
{
	t_list_2	*tmp;

	if (!node || !(*node))
		return ;
	tmp = *node;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		*node = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	del(tmp->content);
	free(tmp);
}
