/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putusnbr_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:15:38 by user              #+#    #+#             */
/*   Updated: 2024/09/26 10:26:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putusnbr_fd(int fd, unsigned int nbr_int)
{
	int		i;
	char	nbr_str[20];

	if (nbr_int == 0)
		return (ft_putchar_fd(fd, '0'));
	i = 0;
	while (nbr_int != 0)
	{
		nbr_str[i] = nbr_int % 10 + '0';
		nbr_int = nbr_int / 10;
		i++;
	}
	nbr_str[i--] = '\0';
	while (i >= 0)
		write(fd, &nbr_str[i--], 1);
	return (ft_strlen(nbr_str));
}
