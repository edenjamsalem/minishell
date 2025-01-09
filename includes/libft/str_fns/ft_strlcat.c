/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:34:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:29:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_size;
	size_t	src_size;

	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	if (size <= dest_size)
		return (src_size + size);
	i = dest_size;
	j = 0;
	while (src[j] && i < (size - 1))
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest_size + src_size);
}
/*
#include <stdio.h>

int	main(void)
{
	char dest[30];
	ft_memset(dest, 0, 30);
	char *src = "AAAAAAAAA";

	dest[0] = 'B';
	printf("%zu\n", ft_strlcat(dest, src, 5));
	printf("%s\n", dest);

}*/
