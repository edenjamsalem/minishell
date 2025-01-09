/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuslong_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 13:54:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 10:05:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_base(char *base)
{
	int		i;

	if (ft_strlen(base) < 2)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		if (chrsetcmp(base[i], &base[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_putuslong_base(unsigned long nbr, char *base)
{
	int		base_len;
	int		digit;
	int		i;
	char	str[32];

	if (check_base(base))
	{
		if (nbr == 0)
			write(1, "0", 1);
		else
		{
			base_len = ft_strlen(base);
			i = 0;
			while (nbr > 0)
			{
				digit = nbr % base_len;
				str[i++] = base[digit];
				nbr /= base_len;
			}
			str[i--] = '\0';
			while (i >= 0)
				write(1, &str[i--], 1);
		}
	}
	return (ft_strlen(str));
}
