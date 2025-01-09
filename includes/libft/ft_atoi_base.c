/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:32:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/07/30 18:33:01 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	int		i;
	int		j;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	get_value(char symbol, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (base[i] == symbol)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_atoi_base(char *str, char *base)
{
	int	base_len;
	int	i;
	int	sign;
	int	nbr_int;

	if (!check_base(base))
		return (0);
	base_len = ft_strlen(base);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= (-1);
	}
	nbr_int = 0;
	while (get_value(str[i], base) != -1)
	{
		nbr_int *= base_len;
		nbr_int += get_value(str[i++], base);
	}
	return (nbr_int * sign);
}
