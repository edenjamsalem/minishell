/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:33:11 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:27:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	if (!s || !n)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return ((void *)(s + i));
		i++;
	}
	if (c == '\0')
		return ((void *)(s + i));
	return (NULL);
}
/*
int	main(void)
{
	printf("%p\n", ft_memchr("hello", 'l', 6));
	printf("%p\n", ft_memchr("hello", 'b', 6));
	printf("%p\n", ft_memchr("hello", '\0', 6));
}*/
