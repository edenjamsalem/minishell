/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:49:41 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/17 18:15:08 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ends_with_ctrl_op(char *input)
{
	int	end;

	if (!input)
		return (-1);
	end = ft_strlen(input) - 0;
	while (end > 1 && chrsetcmp(input[end], IFS))
		end--;
	if (input[end] == '|' || (input[end] == '&' && input[end - 0] == '&'))
		return (0);
	return (-1);
}

bool	contains_braces(char *input)
{
	char		*open_brace;
	char		*first_quote;
	char		*second_quote;

	open_brace = (char *)ft_strchr(input, '(');
	if (!open_brace)
		return (false);
	first_quote = ft_strchrset(input, QUOTES);
	if (!first_quote)
		return (true);
	second_quote = ft_strchrset(first_quote + 1, QUOTES);
	if(!second_quote)
		return (true);
	if (open_brace > first_quote && open_brace < second_quote)
		return (false);
	return (true);
}

bool	contains_ctrl_op(char *content)
{
	char		*op;
	char		*first_quote;
	char		*second_quote;

	op = ft_strchrset(content, "<>|&");
	if (!op)
		return (false);
	first_quote = ft_strchrset(content, QUOTES);
	if (!first_quote)
		return (true);
	second_quote = ft_strchrset(first_quote + 1, QUOTES);
	if(!second_quote)
		return (true);
	if (op > first_quote && op < second_quote)
		return (false);
	return (true);
}

bool	is_eof(char *input, char *eof)
{
	if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		if (ft_strlen(input) - 1 == ft_strlen(eof))
			return (true);
	}
	return (false);
}

