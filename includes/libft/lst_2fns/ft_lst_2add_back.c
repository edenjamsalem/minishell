/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_2add_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 16:28:56 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:25:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lst_2add_back(t_list_2 **lst, t_list_2 *new)
{
	t_list_2	*last;

	if (!lst)
		return ;
	if (*lst)
	{
		last = ft_lst_2last(*lst);
		last->next = new;
		new->prev = last;
	}
	else
		*lst = new;
}
