/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_dict_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:35:39 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:17:35 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	del_dict_node(t_dict **node)
{
	t_dict	*tmp;

	if (!node || !(*node))
		return ;
	tmp = *node;
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	else
		*node = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free_dict(tmp);
}
