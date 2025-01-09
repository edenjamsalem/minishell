/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:13:35 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:13:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	trim_front(char const *s1, char const *set)
{
	unsigned int	start;

	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	return (start);
}

static int	trim_end(char const *s1, char const *set, unsigned int start)
{
	unsigned int	end;

	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int		start;
	unsigned int		end;
	char				*trimmed_str;

	if (!s1 || !set)
		return (NULL);
	start = trim_front(s1, set);
	end = trim_end(s1, set, start);
	trimmed_str = malloc(sizeof(char) * (end - start + 1));
	if (!trimmed_str)
		return (NULL);
	ft_strlcpy(trimmed_str, s1 + start, end - start + 1);
	return (trimmed_str);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strtrim("", ". -"));
//	printf("%s\n", ft_strtrim("", ". -"));
//	printf("%s\n", ft_strtrim(" ...   .. ", ". -"));
//	printf("%s\n", ft_strtrim("hello my name is eden", ". -"));
}*/
