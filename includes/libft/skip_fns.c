/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:15:22 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:08:50 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//This function skips to the next char which is in the set
char	*skip_to(char **text, char *set)
{
	while (**text && !chrsetcmp(**text, set))
		(*text)++;
	return (*text);
}

//This function skips to the next char which is NOT in the set
char	*skip_set(char **text, char *set)
{
	while (**text && chrsetcmp(**text, set))
		(*text)++;
	return (*text);
}

//This function skips to the next char which does not meet the condition
char	*skip_while(char **text, int (*condition)(char))
{
	while (**text && condition(**text))
		(*text)++;
	return (*text);
}

char	*skip_len(char **text, int size)
{
	while (**text && size > 0)
	{
		(*text)++;
		size--;
	}
	return (*text);
}
