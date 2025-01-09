/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:50:11 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:28:41 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	print_digits_count(int nbr)
{
	int		i;
	char	sequence[12];

	i = 0;
	while (nbr != 0)
	{
		sequence[i] = -(nbr % 10) + '0';
		nbr = nbr / 10;
		i++;
	}
	sequence[i--] = '\0';
	while (i >= 0)
		write(1, &sequence[i--], 1);
	return (ft_strlen(sequence));
}

int	ft_putnbr(int nbr)
{
	int	count;

	count = 0;
	if (nbr > 0)
	{
		nbr = nbr * (-1);
		count = print_digits_count(nbr);
	}
	else if (nbr < 0)
	{
		write(1, "-", 1);
		count = (print_digits_count(nbr) + 1);
	}
	else
		return (ft_putchar('0'));
	return (count);
}
