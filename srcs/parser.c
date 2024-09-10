/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:10:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/10 14:10:39 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	parse_input(char *input)
{
	// expand variables OUTSIDE of quotes, e.g. $USER, $HOME
	
	// split input into "words" delimited by space, tab or \n
	// text inside quotes is considered a single word

	// expand variables INSIDE double quotes but NOT single quotes

	// words are tokenized as COMMANDS or ARGUMENTS
}