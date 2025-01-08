/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_op_syntax_check.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:46:26 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 18:40:29 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	brace_count_same(char *input)
{
	int		open_brace_count;
	int		close_brace_count;

	open_brace_count = 0;
	close_brace_count = 0;
	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
		{
			skip_quotes(&input);
			continue ;
		}
		else if (*input == '(')
			open_brace_count++;
		else if (*input == ')')
			close_brace_count++;
		input++;
	}
	if (open_brace_count == close_brace_count)
		return (1);
	ft_fprintf(2, "bash: syntax error: incorrect number of parentheses\n");
	return (0);
}

int	ctrl_op_after_close_brace(char *input)
{
	char	*next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == ')' && *(input + 1) && *(input + 1) != ')')
		{
			input++;
			skip_set(&input, IFS);
			if (*input && !chrsetcmp(*input, "<>&|"))
			{
				next_word = ft_strcut(input, skip_to(&input, IFS));
				ft_perror(SYNTAX, next_word);
				free(next_word);
				return (0);
			}
		}
		else
			input++;
	}
	return (1);
}

int	ctrl_op_after_open_brace(char *input)
{
	char	*next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == '(' && *(input + 1) && *(input + 1) != '(')
		{
			input++;
			skip_set(&input, IFS);
			if (chrsetcmp(*input, "<>&|)"))
			{
				next_word = ft_strcut(input, skip_to(&input, IFS));
				ft_perror(SYNTAX, next_word);
				free(next_word);
				return (1);
			}
		}
		else
			input++;
	}
	return (0);
}

int	ctrl_ops_adjacent(char *input)
{
	char	*next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
		{
			skip_quotes(&input);
			continue ;
		}
		else if (chrsetcmp(*input, "&|") && *input == *(input + 1))
		{
			input += 2;
			skip_set(&input, IFS);
			if (chrsetcmp(*input, "|&)"))
			{
				next_word = ft_strcut(input, skip_to(&input, IFS));
				ft_perror(SYNTAX, next_word);
				free(next_word);
				return (1);
			}
		}
		input++;
	}
	return (0);
}

int	first_word_ctrl_op(char *input)
{
	char	*next_word;

	skip_set(&input, IFS);
	if (chrsetcmp(*input, "&|"))
	{
		next_word = ft_strcut(input, skip_to(&input, IFS));
		ft_perror(SYNTAX, next_word);
		free(next_word);
		return (1);
	}
	return (0);
}
