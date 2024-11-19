/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:47:02 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/19 17:17:56eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_spaces(char **text)
{
	while(chrsetcmp(**text, IFS))
		(*text)++;
}

char	*skip_word(char **text)
{
	while(**text && !chrsetcmp(**text, IFS))
		(*text)++;
	return (*text);
}

char	*skip(char **text, int (*condition)(char))
{
	while (condition(**text))
		(*text)++;
	return (*text);
}

// This function skips to a closing quote if it exists, returns skipped len
int	skip_quotes(char **text)
{
	char	*closing_quote;
	char	*start;

	start = *text;
	closing_quote = (char *)ft_strchr(*text + 1, **text);
	if (closing_quote)
		(*text) = closing_quote + 1;
	else
		(*text)++;
	return (*text - start);
}

