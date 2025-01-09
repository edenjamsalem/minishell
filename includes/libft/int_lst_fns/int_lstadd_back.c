/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_lstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:06:42 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:24:20 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	int_lstadd_back(t_int_lst **lst, t_int_lst *new)
{
	if (*lst)
	{
		int_lstlast(*lst)->next = new;
		new->prev = int_lstlast(*lst);
	}
	else
		*lst = new;
}
