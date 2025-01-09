/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dict.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:39:55 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:17:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	print_dict(t_dict *dict)
{
	while (dict)
	{
		ft_printf("%s=%s\n", dict->key, dict->value);
		dict = dict->next;
	}
}
