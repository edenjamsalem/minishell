/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_dict.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:07:31 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:16:55 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// This function parses a str of form "key=value" or "key" and stores in a dict
static void	assign_key_value(char *str, t_dict *dict)
{
	char	*equal_sign;

	equal_sign = (char *)ft_strchr(str, '=');
	if (equal_sign)
	{
		dict->key = ft_strcut(str, equal_sign);
		dict->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		dict->key = ft_strdup(str);
		dict->value = NULL;
	}
}

t_dict	*str_to_dict(char *str)
{
	t_dict		*dict;

	if (!str || !(*str))
		return (NULL);
	dict = malloc(sizeof(t_dict));
	if (!dict)
		return (NULL);
	assign_key_value(str, dict);
	dict->next = NULL;
	dict->prev = NULL;
	return (dict);
}
