/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/16 13:03:40 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//  checks if a word is a keyword
bool	is_keyword(char *word)
{
	int			i;
	const char	*keywords[] = {"if", "then", "else", "fi", "for", "while", "do",
			"done", "case", "esac", "in", "function", NULL};

	i = 0;
	while (keywords[i] != NULL)
	{
		if (ft_strncmp(word, keywords[i], ft_strlen(keywords[i]) + 1) == 0)
			return (true);
		i++;
	}
	return (false);
}

// checks if a word is a command
bool	is_command(char *word)
{
	if (ft_strncmp(word, "env", 4) == 0)
		return (true);
	else if (ft_strncmp(word, "pwd", 4) == 0)
		return (true);
	else if (ft_strncmp(word, "cd", 3) == 0)
		return (true);
	else if (ft_strncmp(word, "export", 7) == 0)
		return (true);
	else if (ft_strncmp(word, "unset", 6) == 0)
		return (true);
	else if (ft_strncmp(word, "echo", 5) == 0)
		return (true);
	else if (ft_strncmp(word, "cat", 4) == 0)
		return (true);
	else if (ft_strncmp(word, "exit", 4) == 0)
		return (true);
	return (false);
}

// checks if a word is a number
bool	is_number(char *word)
{
	if (*word == '-' || *word == '+')
		word++;
	if (*word == '\0')
		return (false);
	while (*word)
	{
		if (!ft_isdigit(*word))
			return (false);
		word++;
	}
	return (true);
}

// checks if a word is a variable and if that variable exists in env
bool	is_var(char *word)
{
	char	*start;
	char	var_name[word - start + 1];

	if (word[0] != '$' || word[1] == '\0')
		return (false);
	word++;
	if (!ft_isalpha(*word) && *word != '_')
		return (false);
	start = word;
	while (*word && (ft_isalnum(*word) || *word == '_'))
		word++;
	ft_strlcpy(var_name, start, word - start + 1);
	if (getenv(var_name) == NULL)
		return (false);
	return (true);
}

// checks if word is a redirection operator
bool	is_redirect(char *word)
{
	int			i;
	const char	*redirections[] = {"<", "<<", ">", ">>", NULL};

	i = 0;
	while (redirections[i] != NULL)
	{
		if (ft_strncmp(word, redirections[i], ft_strlen(redirections[i])
				+ 1) == 0)
			return (true);
		i++;
	}
	return (false);
}
