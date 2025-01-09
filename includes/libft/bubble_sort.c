/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bubble_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:54:38 by eamsalem          #+#    #+#             */
/*   Updated: 2024/06/16 16:51:48 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rev_bubble_sort_arr(int *arr, int size)
{
	int	i;
	int	swaps;

	while (1)
	{
		swaps = 0;
		i = 0;
		while (i < size - 1)
		{
			if (arr[i] < arr[i + 1])
			{
				ft_swap(&arr[i], &arr[i + 1]);
				swaps++;
			}
			i++;
		}
		if (swaps == 0)
			break ;
	}
}

void	bubble_sort_arr(int *arr, int size)
{
	int	i;
	int	swaps;

	while (1)
	{
		swaps = 0;
		i = 0;
		while (i < size - 1)
		{
			if (arr[i] > arr[i + 1])
			{
				ft_swap(&arr[i], &arr[i + 1]);
				swaps++;
			}
			i++;
		}
		if (swaps == 0)
			break ;
	}
}
