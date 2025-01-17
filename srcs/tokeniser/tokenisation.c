/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:44:03 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:26:00 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// find the next token in input matching ref
int	find_next_token(t_token *tokens, enum e_token ref)
{
	int	i;

	i = 0;
	while (tokens[i] != END)
	{
		if (tokens[i] == ref)
			return (i);
		i++;
	}
	return (-1);
}

int	skip_redirect(t_token *tokens, int index)
{
	int	i;

	i = index;
	while (tokens[i] == REDIRECT || tokens[i] == FILE_)
		i++;
	return (i);
}

// initial tokenisation for redirections, control ops and quotes only
// had to put control ops here as well so i can keep track of them before
// i have to set cmd->condition for cmds in input
t_token	*primary_tokenisation(t_arrlst *words, t_token *tokens)
{
	int	i;

	i = 0;
	while (i < words->count)
	{
		if (is_redirect(words->content[i]))
			tokens[i] = REDIRECT;
		else if (is_pipe(words->content[i]))
			tokens[i] = PIPE;
		else
			tokens[i] = TEXT;
		i++;
	}
	return (tokens);
}

// consequent tokenisation for all other tokens + creation of cmds list
t_token	*secondary_tokenisation(t_arrlst *words, t_token *tokens)
{
	int	i;

	i = 0;
	while (words->content[i])
	{
		if (is_file(i, tokens))
			tokens[i] = FILE_;
		i++;
	}
	i = 0;
	while (i < words->count)
	{
		if (is_redirect(words->content[i]))
			i = skip_redirect(tokens, i);
		else if (is_command(i, tokens) && tokens[i] == TEXT)
			tokens[i++] = CMD;
		else
			i++;
	}
	return (tokens);
}

t_token	*tokenise(t_arrlst *words)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token) * (words->count + 1));
	if (!tokens)
		return (NULL);
	tokens[words->count] = END;
	tokens = primary_tokenisation(words, tokens);
	tokens = secondary_tokenisation(words, tokens);
	return (tokens);
}
