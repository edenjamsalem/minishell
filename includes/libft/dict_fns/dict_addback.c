/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_addback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:30:09 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:17:13 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	dict_addback(t_dict **dict, t_dict *new)
{
	t_dict	*last;

	if (!dict)
		return ;
	if (*dict)
	{
		last = dict_last(*dict);
		last->next = new;
		new->prev = last;
	}
	else
		*dict = new;
}
