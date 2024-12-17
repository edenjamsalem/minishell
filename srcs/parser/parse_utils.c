/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:09 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 15:54:32 by eamsalem         ###   ########.fr       */
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

static void	remove_quotes(char *text)
{
	char	quote_to_del;

	quote_to_del = *(ft_strchrset(text, QUOTES));
	while (*text)
	{
		if (*text == quote_to_del)
			del_char(text);	
		else
			text++;
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

	if (!(*input) || !(*expanded) || !(envp_dict))
		return ;	
	(*input)++;	
	key = ft_strcut(*input, skip_to(input, IFS));
	if (ft_strchrset(key, QUOTES)) // check if i still need this 
		remove_quotes(key);
	value = get_dict_value(key, envp_dict);
	value_len = ft_strlen(value);
	if (value)
	{
		ft_strlcpy(*expanded, value, value_len + 1);	
		skip_len(expanded, value_len);
	}
	free(key);
}
