/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:10:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/11 15:17:58 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	lex_input(char *input)
{
	// expand variables OUTSIDE of quotes, e.g. $USER, $HOME
		// if " or ' encountered, skip until next " or '
		// search string for '$'
		// if text after $ is valid variable, expand variable
		// else ... 
	
	// split input into "words", i.e. strings delimited by space, tab or \n
	// text inside quotes is considered a single word

	// expand variables INSIDE double quotes but NOT single quotes

	// words are tokenized as COMMANDS, ARGUMENTS, KEYWORDS, SPECIAL SYMBOLS

}