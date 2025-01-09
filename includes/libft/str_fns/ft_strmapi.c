/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:25:22 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:30:50 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h" 
/*
char	f(unsigned int i, char c)
{
	if (c >= 'a' && c <= 'z' && i < 10)
		c -= 32;
	return (c);
}
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_s;
	int		i;

	new_s = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		new_s[i] = f(i, s[i]);
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%s\n", ft_strmapi("hello", f));
}*/
