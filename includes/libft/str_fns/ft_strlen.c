/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:33:54 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/15 17:11:22 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h" 

size_t	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
/*
#include <stdio.h>

int	main(void)
{
	char *null = NULL;
	
	printf("%zu\n", ft_strlen("hello"));
	printf("%zu\n", ft_strlen(null));
	printf("%zu\n", ft_strlen("123456789"));
}
*/