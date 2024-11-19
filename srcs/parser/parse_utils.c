/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:09 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/18 16:59:06 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_quoted_text(char **input, char **expanded)
{
	char	*closing_quote;

	if (!(*input) || !(*expanded))
		return ;
	closing_quote = (char *)ft_strchr(*input + 1, **input);
	if (closing_quote)
		ft_strlcpy(*expanded, *input, (closing_quote - *input + 2));
	else
		**expanded = **input;
	skip_quotes(input);
	skip_quotes(expanded);
}

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict)
{
	char	*key;
	char	*value;

	if (!(*input) || !(*expanded) || !(envp_dict))
		return ;	
	(*input)++;	
	key = ft_strcut(*input, skip_alnum(input));
	value = get_dict_value(key, envp_dict);
	if (value)
	{
		ft_strlcpy(*expanded, value, ft_strlen(value) + 1);	
		skip_word(expanded);
	}
	skip_alnum(input);
	free(key);
}

static void	remove_quotes(char *text)
{
	char	quote_to_del;
	int		i;

	quote_to_del = *(ft_strchrset(text, QUOTES));
	while (*text)
	{
		if (*text == quote_to_del)
		{
			i = 0;
			while (text[i + 1])
			{
				text[i] = text[i + 1];
				i++;
			}
			text[i] = '\0';
		}
		text++;
	}
}

void	quote_removal(t_list_2 *input)
{
	t_word	*word;

	while (input)
	{
		word = (t_word *)(input->content);
		if (ft_strchrset(word->text, QUOTES))
			remove_quotes(word->text);
		input = input->next;
	}
}