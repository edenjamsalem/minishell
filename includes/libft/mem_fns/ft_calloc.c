/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:50:05 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:26:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (nmemb > 0 && SIZE_MAX / nmemb < size)
		return (NULL);
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i;
	int	*dest;
	
	i = 0;
	dest = ft_calloc(6, sizeof(int));
	while(i < 6)
		printf("%d\n", dest[i++]); 
}*/
