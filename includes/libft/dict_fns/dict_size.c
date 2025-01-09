/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:48:58 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:18:20 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	dict_size(t_dict *dict)
{
	int	size;

	size = 0;
	while (dict)
	{
		size++;
		dict = dict->next;
	}
	return (size);
}
