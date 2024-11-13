/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:47:02 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/13 16:15:07 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_spaces(char **text)
{
	while(**text && chrsetcmp(**text, SPACES))
		(*text)++;
}

void	skip_quotes(char **text, char quote)
{
	char	*closing_quote;

	closing_quote = (char *)ft_strchr(*text + 1, quote);
	if (closing_quote)
		(*text) = closing_quote + 1;
	else {
		(*text)++;
	}
}

char	*cut_word(char *start, char *end)
{
	char 	*text;
	char 	*tmp;
	t_word	*word;

	text = malloc(sizeof(char) * (end - start + 1));
		//malloc error
	tmp = text;
	while (start < end)
		*tmp++ = *start++;
	*tmp = '\0';
	return (text);
}