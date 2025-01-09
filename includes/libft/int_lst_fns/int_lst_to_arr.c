/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_lst_to_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:29:23 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:24:11 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	*int_lst_to_arr(t_int_lst *lst, int size)
{
	int	*arr;
	int	i;

	if (!lst || !(lst) || size < 0)
		return (NULL);
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size)
	{
		arr[i++] = lst->content;
		lst = lst->next;
	}
	return (arr);
}
