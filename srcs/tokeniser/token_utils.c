/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/04 17:22:09 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// instead of quotes do a check for FILE after REDIRECT	(grammar check)

// finds both types of redirection
bool	is_redirect(void *word)
{
	if (ft_match(word, "<") || ft_match(word, ">"))
		return (true);
	else if (ft_match(word, ">>") || ft_match(word, "<<"))
		return (true);
	return (false);
}

bool	is_file(int index, t_token *tokens)
{
	if (get_prev_token(tokens, index) == REDIRECT)
		return (true);
	return (false);
}

// finds cmds
// checks if index is 0 or that prev token is PIPE/CONTROL OP
bool	is_command(int index, t_token *tokens)
{
	if (index == 0)
		return (true);
	else if (get_prev_token(tokens, index) == CTRL_OP)
		return (true);
	else if (get_prev_token(tokens, index) == PIPE)
		return (true);
	return (false);
}

// finds and tokenises control ops
// check if prev token is CONTROL OP then it's error (grammar check)
bool	is_control(void *word)
{
	if (ft_match(word, "&&") || ft_match(word, "||"))
		return (true);
	return (false);
}

// finds and tokenises pipes
// check if prev token is PIPE then it's error (grammar check)
bool	is_pipe(void *word)
{
	if (ft_match(word, "|"))
		return (true);
	return (false);
}
