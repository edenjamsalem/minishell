/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dict_entry.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:26:54 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:17:27 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_dict	*get_dict_entry(char *key, t_dict *dict)
{
	while (dict)
	{
		if (ft_match(key, dict->key))
			return (dict);
		dict = dict->next;
	}
	return (NULL);
}
