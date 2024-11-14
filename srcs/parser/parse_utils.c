/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:47:02 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 11:58:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_spaces(char **text)
{
	while(**text && chrsetcmp(**text, SPACES))
		(*text)++;
}

char	*skip_word(char **text)
{
	while(**text && !chrsetcmp(**text, SPACES))
		(*text)++;
	return (*text);
}

// This function skips to closing quote if exists, returns skipped len
int	skip_quotes(char **text, char quote)
{
	char	*closing_quote;
	char	*start;

	start = *text;
	closing_quote = (char *)ft_strchr(*text + 1, quote);
	if (closing_quote)
		(*text) = closing_quote + 1;
	else
		(*text)++;
	return (*text - start);
}
