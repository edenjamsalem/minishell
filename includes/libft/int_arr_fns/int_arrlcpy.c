/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_arrlcpy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:53:49 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 16:32:56 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	*int_arrlcpy(int *dest, int *src, int size)
{
	int	i;
	int	*tmp;

	if (!src || !dest)
		return (NULL);
	i = 0;
	tmp = dest;
	while (i < size)
	{
		*tmp = *src;
		tmp++;
		src++;
	}
	return (dest);
}
