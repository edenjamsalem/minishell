/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:55:54 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:25:58 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

void	skip_braces(char **input)
{
	int		open_brace_count;
	int		close_brace_count;

	(*input)++;
	open_brace_count = 1;
	close_brace_count = 0;
	while (**input && open_brace_count > close_brace_count)
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
