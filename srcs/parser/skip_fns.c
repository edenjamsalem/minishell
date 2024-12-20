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

//This function skips to the next char which is in the set
char	*skip_to(char **text, char *set)
{
	while(**text && !chrsetcmp(**text, set))
		(*text)++;
	return (*text);
}

//This function skips to the next char which is NOT in the set
char	*skip_set(char **text, char *set)
{	
	while(**text && chrsetcmp(**text, set))
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

void skip_braces(char **input)
{
	int		open_brace_count;
	int		close_brace_count;
	

	(*input)++;
	open_brace_count = 1;
	close_brace_count = 0;
	while(**input && open_brace_count > close_brace_count)
	{
		if (chrsetcmp(**input, QUOTES))
			skip_quotes(input);
		else if (**input == '(')
			open_brace_count++;
		else if (**input == ')')
			close_brace_count++;
		(*input)++;
	}
}