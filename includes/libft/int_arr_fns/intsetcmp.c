/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intsetcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:35:54 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 16:33:08 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	intsetcmp(int nbr, int *set, int size)
{
	int	i;

	if (!set || size < 1)
		return (0);
	i = 0;
	while (i < size)
	{
		if (set[i++] == nbr)
			return (1);
	}
	return (0);
}
/*
int	main(void)
{
	int	arr[5];
	int	*tmp;
	int i;

	i = 1;
	tmp = arr;
	while (i < 6)
	{
		*tmp = i++;
		tmp++;
	}
	printf("%d\n", intsetcmp(1, arr, 5));
	printf("%d\n", intsetcmp(5, arr, 5));
	printf("%d\n", intsetcmp(6, arr, 5));
}*/
