/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:10:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/12 13:50:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	// expand variables OUTSIDE of quotes, e.g. $USER, $HOME
		// if " or ' encountered, skip until next " or '
		// search string for '$'
		// if text after $ is valid variable, expand variable
		// else ... 
	
	// split input into "words", i.e. strings delimited by space, tab or \n
	// text inside quotes is considered a single word

	// words are tokenized as COMMANDS, ARGUMENTS, KEYWORDS, SPECIAL SYMBOL

	// expand variables INSIDE double quotes but NOT single quotes

	
void	skip(char *text, int *i, char delimeter)
{
	while(text[*i] && text[*i] != delimeter)
		(*i)++;
}
void	parse_input_exc_quotes(char *input)
{
	int i;

	while (input[i])
	{
		if (input[i] == '\"')
		{
			skip(input, &i, '\"');
			continue ;
		}
		else if (input[i] == '\"')
		{
			skip(input, &i, '\"');
			continue ;
		}
		else if (input[i] == '$')
		{
			expand_var(input + i);
			continue ;
		}
		i++;
	}
}

void	parse(char *input)
{
	parse_input_exc_quotes(input);
	expand_vars_inside_quotes();
	tokenize()
}