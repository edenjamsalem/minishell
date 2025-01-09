/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_last.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:26:52 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 11:29:43 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// This function returns a pointer to the last node in a dict

t_dict	*dict_last(t_dict *dict)
{
	if (!dict)
		return (NULL);
	while (dict->next)
		dict = dict->next;
	return (dict);
}
