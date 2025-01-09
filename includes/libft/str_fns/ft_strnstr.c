/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:32:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:30:42 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

const char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (little[0] == '\0')
		return (&big[0]);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while ((big[i + j] == little[j]) && (i + j < len))
		{
			j++;
			if (little[j] == '\0')
				return (&big[i]);
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	printf("%p\n", ft_strnstr("Hello my name is Eden", "name", 22));
	printf("%p\n", ft_strnstr("Hello my name is Eden", "my", 22));
	printf("%p\n", ft_strnstr("Hello my name is Eden", "", 22));
}*/
