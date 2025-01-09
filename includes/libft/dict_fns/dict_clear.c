/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:19:32 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 11:22:31 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	dict_clear(t_dict **dict)
{
	t_dict	*tmp;

	if (!dict || !*dict)
		return ;
	while (dict && *dict)
	{
		tmp = (*dict)->next;
		free_dict(*dict);
		*dict = tmp;
	}
}
