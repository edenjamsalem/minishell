/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:40:08 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 16:40:10 by eamsalem         ###   ########.fr       */
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

void	remove_braces(char *input)
{
	char	*start;
	char	*end;

	start = input;
	end = input + ft_strlen(input) - 1;
	while (*start && *start != '(')
		start++;
	while (end > input && *end != ')')
		end--;
	if (*end == ')')
		del_char(end);
	if (*start == '(')
		del_char(start);
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

bool	contains(char *word, char *set)
{
	char		*first_quote;
	char		*second_quote;

	set = ft_strchrset(word, set);
	if (!set)
		return (false);
	first_quote = ft_strchrset(word, QUOTES);
	if (!first_quote)
		return (true);
	second_quote = ft_strchrset(first_quote + 1, QUOTES);
	if (!second_quote)
		return (true);
	if (set > first_quote && set < second_quote)
		return (false);
	return (true);
}
