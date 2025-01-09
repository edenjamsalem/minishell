/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:26:12 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 10:20:36 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	print_digits_fd(int fd, int nbr_int)
{
	int		i;
	char	nbr_str[12];

	i = 0;
	while (nbr_int != 0)
	{
		nbr_str[i] = -(nbr_int % 10) + '0';
		nbr_int /= 10;
		i++;
	}
	nbr_str[i--] = '\0';
	while (i >= 0)
		write(fd, &nbr_str[i--], 1);
	return (ft_strlen(nbr_str));
}

int	ft_putnbr_fd(int fd, int nbr)
{
	if (nbr > 0)
		return (print_digits_fd(fd, -nbr));
	else if (nbr < 0)
	{
		write(fd, "-", 1);
		return (print_digits_fd(fd, nbr) + 1);
	}
	else
		return (ft_putchar_fd(fd, '0'));
}
/*
int main(void)
{
	printf("%d", ft_putnbr_fd(1, -10));
}
*/