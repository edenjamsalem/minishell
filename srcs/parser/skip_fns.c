/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:47:02 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/15 16:34:20 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*skip_alnum(char **text)
{
	while(ft_isalnum(**text))
		(*text)++;
	return (*text);
}

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

// This function skips to a closing quote if it exists, returns skipped len
int	skip_quotes(char **text)
{
	char	*closing_quote;
	char	*start;

	if (!*text || !(*text + 1) || **text == '\0')
		return (0);
	start = *text;
	closing_quote = (char *)ft_strchr(*text + 1, **text);
	if (closing_quote)
		(*text) = closing_quote + 1;
	else
		(*text)++;
	return (*text - start);
}

