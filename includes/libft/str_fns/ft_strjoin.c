/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:10:56 by eamsalem          #+#    #+#             */
/*   Updated: 2024/10/28 17:58:18 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	int		s1_len;
	int		s2_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	join_str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!join_str)
		return (NULL);
	ft_strlcpy(join_str, s1, s1_len + 1);
	ft_strlcpy(join_str + s1_len, s2, s2_len + 1);
	return (join_str);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strjoin("hello ", "goodbye"));
}
*/