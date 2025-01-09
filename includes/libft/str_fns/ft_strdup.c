/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:54:35 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 14:57:53 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h" 

char	*ft_strdup(const char *str)
{
	char	*cpy;
	int		size;

	if (!str || !(*str))
		return (NULL);
	size = ft_strlen(str);
	cpy = malloc(sizeof(char) * (size + 1));
	if (!cpy)
		return (NULL);
	ft_strlcpy(cpy, str, size + 1);
	return (cpy);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strdup("hello"));
}*/
