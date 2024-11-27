/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/26 14:32:53 by eamsalem         ###   ########.fr       */
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

// create a new cmd struct to put inside cmds list
t_cmd	*create_cmd(t_list_2 *input)
{
	t_cmd	*cmd;
	t_word	*word;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->cmd = ((t_word *)(input->content))->text;
	cmd->args = NULL;
	word = find_next_token(input, CTRL_OP);
	if (word)
	{
		if (ft_strncmp(word->text, "&&", 3) == 0)
			cmd->conditional = AND;
		else if (ft_strncmp(word->text, "||", 3) == 0)
			cmd->conditional = OR;
	}
	else
		cmd->conditional = NONE;
	return (cmd);
}

// initial tokenisation for redirections, control ops and quotes only
// had to put control ops here as well so i can keep track of them before
// i have to set cmd->condition for cmds in input
t_list_2	*primary_tokenisation(t_shell *shell)
{
	t_word		*word;
	t_list_2	*temp;

	temp = shell->input;
	while (temp)
	{
		word = (t_word *)temp->content;
		if (is_redirect(word) || is_quotes(word))
		{
			temp = temp->next;
			continue ;
		}
		else if (is_control(word))
		{
			shell->exit_status = true;
				// change flag to indicate we need to watch exit status of cmds
			temp = temp->next;
			continue ;
		}
		else
			temp = temp->next;
	}
	return (shell->input);
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

// t_list_2 *tokeniser(t_shell *shell)
// function that tokenises, reparses and then retokenises again
