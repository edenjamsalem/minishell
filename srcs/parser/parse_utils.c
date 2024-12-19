/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:09 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/19 16:11:30 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	del_char(char *text)
{
	int	i;
		
	i = 0;
	while (text[i + 1])
	{
		text[i] = text[i + 1];
		i++;
	}
	text[i] = '\0';
}

void	remove_quotes(char *text)
{
	char	*open_quote;
	char	quote_to_del;

	while (*text)
	{
		open_quote = ft_strchrset(text, QUOTES);		
		if (!open_quote)
			break ;
		quote_to_del = *(open_quote);
		del_char(open_quote);
		while (*text)
		{
			if (*text == quote_to_del)
			{
				del_char(text);
				break ;
			}
			else
				text++;
		}
	}
}

void	quote_removal(t_arrlst *input)
{
	int		i;

	i = 0;
	while (i < input->count)
	{
		if (ft_strchrset(input->content[i], QUOTES))
			remove_quotes(input->content[i]);
		i++;
	}
}

void	copy_quoted_text(char **input, char **expanded)
{
	char	*closing_quote;

	if (!(*input) || !(*expanded))
		return ;
	closing_quote = (char *)ft_strchr(*input + 1, **input);
	if (closing_quote)
	{
		ft_strlcpy(*expanded, *input, (closing_quote - *input + 2));
		skip_quotes(input);
		skip_quotes(expanded);
	}
	else
		*(*expanded)++ = *(*input)++;
}

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict)
{
	char	*key;
	char	*value;
	int		value_len;

	key = ft_strcut(*input, skip_while(input, ft_isalnum));
	value = get_dict_value(key, envp_dict);
	value_len = ft_strlen(value);
	if (value)
	{
		ft_strlcpy(*expanded, value, value_len + 1);	
		skip_len(expanded, value_len);
	}
	free(key);
}
