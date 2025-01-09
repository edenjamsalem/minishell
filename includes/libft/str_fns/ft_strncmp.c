/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:49:35 by eamsalem          #+#    #+#             */
/*   Updated: 2024/10/29 17:08:03 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (i < n && s1[i] && s2[i] && (s1[i] == s2[i]))
		i++;
	if (i < n)
		return (s1[i] - s2[i]);
	return (0);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%d\n", ft_strncmp("hello", "hello", 3)); 
	printf("%d\n", ft_strncmp("hello", "hell", 4)); 
	printf("%d\n", ft_strncmp("hello", "", 4)); 
}
*/