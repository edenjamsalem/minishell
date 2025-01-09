/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_to_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:46:44 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:18:00 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	**dict_to_arr(t_dict *dict)
{
	char	**arr;
	int		key_len;
	int		value_len;
	int		i;

	arr = malloc(sizeof(char *) * (dict_size(dict) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (dict)
	{
		key_len = ft_strlen(dict->key);
		value_len = ft_strlen(dict->value);
		arr[i] = malloc(sizeof(char) * (key_len + value_len + 2));
		if (!arr[i])
			return (NULL);
		ft_strlcpy(arr[i], dict->key, key_len + 1);
		arr[i][key_len] = '=';
		ft_strlcpy((arr[i] + key_len + 1), dict->value, value_len + 1);
		dict = dict->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}
