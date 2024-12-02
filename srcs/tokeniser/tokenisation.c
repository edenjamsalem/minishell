/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/02 18:48:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// find the next token in input matching ref
t_word	*find_next_token(t_list_2 *input, enum e_token ref)
{
	t_word		*word;
	t_list_2	*temp;

	temp = input;
	while (temp)
	{
		word = (t_word *)temp->content;
		if (word->token == ref)
			return (word);
		temp = temp->next;
	}
	return (NULL);
}

// initial tokenisation for redirections, control ops and quotes only
// had to put control ops here as well so i can keep track of them before
// i have to set cmd->condition for cmds in input
e_token	*primary_tokenisation(void **words)
{
	int	i;
	// loop through array
	i = 0;
	while (words[i])
	{
		if (is_redirect(words[i]))
		{
			i++;
			continue ;
		}
		else if (is_control(words[i]))
		{
			i++;
			continue ;
		}
		else
			i++;
	}
	return (words);
}

// consequent tokenisation for all other tokens + creation of cmds list
t_list_2	*secondary_tokenisation(t_shell *shell)
{
	t_word		*word;
	t_list_2	*temp;

	temp = shell->input;
	while (temp)
	{
		word = (t_word *)temp->content;
		if (is_command(word))
		{
			ft_lst_2add_back(&shell->cmds, ft_lst_2new(create_cmd(temp)));
			temp = temp->next;
			continue ;
		}
		else if (is_pipe(word))
		{
			temp = temp->next;
			continue ;
		}
		else
			temp = temp->next;
	}
	return (shell->input);
}

// e_token *tokeniser(t_arrlst *words) > needs to return an e_token *tokens;
// grammar check function(s) after tokenisation 
// function that tokenises, reparses and then retokenises again

