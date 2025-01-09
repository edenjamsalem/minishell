/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_dict_value.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:17:36 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 15:19:26 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	set_dict_value(char *key, char *new_value, t_dict *dict)
{
	while (dict)
	{
		if (ft_match(key, dict->key))
		{
			free(dict->value);
			dict->value = new_value;
			return ;
		}
		dict = dict->next;
	}
}
