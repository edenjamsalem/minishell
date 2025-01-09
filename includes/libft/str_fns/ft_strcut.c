/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:59:08 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:15:46 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// This function copies a str segment between two pointers, excl *end
char	*ft_strcut(char *start, char *end)
{
	char	*segment;
	char	*tmp;

	if (!start || !end)
		return (NULL);
	segment = malloc(sizeof(char) * (end - start + 1));
	if (!segment)
		return (NULL);
	tmp = segment;
	while (start < end)
		*tmp++ = *start++;
	*tmp = '\0';
	return (segment);
}
/*
int main(void)
{
	char *str = "hello my name is eden";

	printf("%s\n", ft_strcut(str, str + 1));
}
*/