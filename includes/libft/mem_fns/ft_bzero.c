/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:18:13 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:26:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*tmp;

	tmp = s;
	i = 0;
	while (i < n)
		tmp[i++] = '\0';
	return (s);
}
/*
#include <stdio.h>
int	main(void)
{
	int	j = 0;
	char	memset[10];

	ft_bzero(memset, 6);

	while (j < 6)
		printf("%d ", memset[j++]);
}*/
