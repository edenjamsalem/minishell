/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temptokenisation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:19 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/26 14:32:53 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks if a word is control operator
bool	is_control(char *word)
{
	int		i;
	char	*controls[] = {"||", "&&", NULL};

	i = 0;
	while (controls[i] != NULL)
	{
		if (ft_strncmp(word, controls[i], ft_strlen(controls[i]) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

// checks if token is keyword, cmd or control op and sets their type
bool	is_special_token(char *word, enum e_token *token)
{
	if (is_command(word))
	{
		*token = CMD;
		return (true);
	}
	else if (is_control(word))
	{
		*token = CTRL_OP;
		return (true);
	}
	return (false);
}

// basic tokeniser, will have to be expanded 
t_list_2	*tokenise(t_shell *shell)
{
	t_word		*word;
	t_list_2	*temp;

	temp = shell->input;
	while (temp)
	{
		word = (t_word *)temp->content;
		if (is_special_token(word->text, &word->token) || is_quotes(word->text,
				&word->token))
		{
			temp = temp->next;
			continue ;
		}
		else if (is_redirect(word->text))
			word->token = REDIRECT_OP;
		else
			word->token = TEXT;
		temp = temp->next;
	}
	return (shell->input);
}
