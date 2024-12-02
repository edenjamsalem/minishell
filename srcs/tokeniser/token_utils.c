/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/02 18:49:31 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// instead of quotes do a check for FILE after REDIRECT	 

// finds and tokenises both types of redirection
bool	is_redirect(void *word)
{
	if (MATCH(word, "<") || MATCH(word, ">") || MATCH(word, ">>") || MATCH(word,
			"<<"))
		return (true);
	return (false);
}

// finds and tokenises cmds
// check if index is 0 or that prev token is PIPE/CONTROL OP
bool	is_command(t_word *word)
{
	i = 0;
	while (cmds_key[i] != NULL)
	{
		if (ft_strncmp(word->text, cmds_key[i], ft_strlen(word->text)) == 0)
		{
			word->token = CMD;
			return (true);
		}
		i++;
	}
	return (false);
}

// finds and tokenises control ops
// check if prev token is CONTROL OP then it's error
bool	is_control(t_word *word)
{
	int		i;
	char	*controls[] = {"||", "&&", NULL};

	i = 0;
	while (controls[i] != NULL)
	{
		if (ft_strncmp(word, controls[i], ft_strlen(controls[i]) + 1) == 0)
		{
			word->token = CTRL_OP;
			return (true);
		}
		i++;
	}
	return (false);
}

// finds and tokenises pipes
// check if prev token is PIPE then it's error
bool	is_pipe(t_word *word)
{
	if (ft_strncmp(word->text, "|", 2) == 0)
	{
		word->token = PIPE;
		return (true);
	}
	return (false);
}
