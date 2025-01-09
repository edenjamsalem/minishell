/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 15:59:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:15:57 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Returns a pointer to the first occurrence of a any chr from "set" in "str".
char	*ft_strchrset(char *str, char *set)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (chrsetcmp(str[i], set))
			return (&str[i]);
		i++;
	}
	return (NULL);
}
