/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:15:50 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:30:25 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	unsigned int	i;
	size_t			sub_len;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	sub_len = ft_strlen(s + start);
	if (sub_len >= len)
		sub_len = len;
	substr = malloc(sizeof(char) * (sub_len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_substr("123456789", 0, 9));
	printf("%s\n", ft_substr("hello my name is eden", 5, 20));
	printf("%s\n", ft_substr("hello my name is eden", 0, 10));
}*/
