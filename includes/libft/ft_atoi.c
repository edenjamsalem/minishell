/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:26:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:03:10 by eamsalem         ###   ########.fr       */
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

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		nbr_int;

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
/*
#include <limits.h>

int	main(void)
{
	printf("%d\n", ft_atoi("-1"));
	printf("%d\n", ft_atoi("	+42Lyon"));
	printf("%d\n", ft_atoi("  -2147483647"));
	printf("%d\n", ft_atoi(""));
}
*/