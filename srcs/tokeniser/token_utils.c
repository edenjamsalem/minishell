/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:42 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/06 14:25:59 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// returns previous token in array, mainly for code readability
t_token	get_prev_token(t_token *tokens, int index)
{
	if (index == 0)
		return (END);
	return (tokens[index - 1]);
}

// finds both types of redirection
bool	is_redirect(void *word)
{
	if (ft_strchrset((char *)word, QUOTES))
		skip_quotes((char **)&word);
	if (ft_match(word, "<") || ft_match(word, ">"))
		return (true);
	else if (ft_match(word, ">>") || ft_match(word, "<<"))
		return (true);
	return (false);
}

bool	is_file(int index, t_token *tokens)
{
	if (get_prev_token(tokens, index) == REDIRECT && tokens[index] != REDIRECT)
		return (true);
	return (false);
}

// finds cmds
// checks if index is 0 or that prev token is PIPE/CONTROL OP
bool	is_command(int index, t_token *tokens)
{
	if (index == 0 && tokens[0] != REDIRECT)
		return (true);
	else if (get_prev_token(tokens, index) == FILE_)
		return (true);
	else if (get_prev_token(tokens, index) == PIPE)
		return (true);
	return (false);
}

// finds and tokenises pipes
// check if prev token is PIPE then it's error (grammar check)
bool	is_pipe(void *word)
{
	if (ft_strchrset((char *)word, QUOTES))
		skip_quotes((char **)&word);
	if (ft_match(word, "|"))
		return (true);
	return (false);
}
