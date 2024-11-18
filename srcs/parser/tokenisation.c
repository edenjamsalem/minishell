/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 09:09:19 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/16 14:01:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks if a word is control operator
bool	is_control(char *word)
{
	int		i;
	char	*controls[] = {"||", "&&", "&", "|", NULL};

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
	if (is_keyword(word))
	{
		*token = KEYWORD;
		return (true);
	}
	else if (is_command(word))
	{
		*token = CMD;
		return (true);
	}
	else if (is_control(word))
	{
		*token = CONTROL_OP;
		return (true);
	}
	return (false);
}

// checks if a word is double or single quotes and sets enum
bool	is_quotes(char *word, enum e_token *token)
{
	if (ft_strncmp(word, "\"", 1) == 0)
	{
		*token = D_QUOTES;
		return (true);
	}
	else if (ft_strncmp(word, "'", 1) == 0)
	{
		*token = S_QUOTES;
		return (true);
	}
	return (false);
}

// checks if a word is the start of a comment, a glob or a new line
bool	is_misc(char *word, enum e_token *token)
{
	if (word[0] == '#')
	{
		*token = COMMENT;
		return (true);
	}
	else if (word[0] == '*')
	{
		*token = GLOB;
		return (true);
	}
	else if (ft_strncmp(word, "\n", 1) == 0)
	{
		*token = NLINE;
		return (true);
	}
	return (false);
}

// basic tokeniser, will have to be expanded 
t_list_2	*tokenise(t_list_2 *parsed_input)
{
	t_word		*word;
	t_list_2	*temp;

	temp = parsed_input;
	while (temp)
	{
		word = (t_word *)temp->content;
		if (is_special_token(word->text, &word->token) || is_quotes(word->text,
				&word->token) || is_misc(word->text, &word->token))
		{
			temp = temp->next;
			continue ;
		}
		else if (is_number(word->text))
			word->token = NUMBER;
		else if (is_var(word->text))
			word->token = VAR;
		else if (is_redirect(word->text))
			word->token = REDIRECT;
		else
			word->token = TEXT;
		temp = temp->next;
	}
	return (parsed_input);
}
