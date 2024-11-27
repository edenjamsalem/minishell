/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/26 14:32:53 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// finds and tokenises both types of redirection
bool	is_redirect(t_word *word)
{
	if (ft_strncmp(word->text, "<", 2) == 0 || ft_strncmp(word, ">", 2) == 0)
	{
		word->token = REDIRECT_OP;
		return (true);
	}
	else if (ft_strncmp(word->text, "< ", 3) == 0 || ft_strncmp(word, "> ", 3) == 0)
	{
		word->token = REDIRECT_FILE;
		return (true);
	}
	return (false);
}

// finds and tokenises quotes
bool	is_quoted(t_word *word)
{
	if (ft_strncmp(word->text, "\"", 1) == 0 || ft_strncmp(word, "\'", 1) == 0)
	{
		word->token = QUOTED;
		return (true);
	}
	return (false);
}

// finds and tokenises cmds
bool	is_command(t_word *word)
{
	int			i;
	char		*cmds_key[] = {"env", "pwd", "cd", "export", "unset", "echo",
				"exit", NULL};

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
bool	is_pipe(t_word *word)
{
	if (ft_strncmp(word->text, "|", 2) == 0)
	{
		word->token = PIPE;
		return (true);
	}
	return (false);
}
