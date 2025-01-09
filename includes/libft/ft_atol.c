/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 12:21:18 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:05:00 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_whitespace(const char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	return (i);
}

static int	get_sign(char sign)
{
	if (sign == '-')
		return (-1);
	return (1);
}

long	ft_atol(const char *str)
{
	long	i;
	long	sign;
	long	nbr_int;

	i = skip_whitespace(str);
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
		sign = get_sign(str[i++]);
	nbr_int = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr_int *= 10;
		nbr_int += str[i] - '0';
		i++;
	}
	return (nbr_int * sign);
}
