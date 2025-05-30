/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:56:16 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 16:34:28 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_seq_count(char *input)
{
	int	count;

	if (!input || !(*input))
		return (0);
	count = 1;
	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == '(')
			skip_braces(&input);
		else if (chrsetcmp(*input, "&|") && *input == *(input + 1))
		{
			count++;
			input++;
		}
		else
			input++;
	}
	return (count);
}

t_ctrl_op	assign_ctrl_op(char **input)
{
	char	ctrl_op[3];

	if (!chrsetcmp(**input, "&|"))
		return (NONE);
	ctrl_op[0] = **input;
	ctrl_op[1] = *(*input + 1);
	ctrl_op[2] = '\0';
	*input += 2;
	if (ft_match(ctrl_op, "&&"))
		return (AND);
	else if (ft_match(ctrl_op, "||"))
		return (OR);
	return (NONE);
}

char	*copy_text(char **input)
{
	char	*start;

	if (!input || !(*input))
		return (NULL);
	skip_set(input, IFS);
	start = *input;
	while (**input)
	{
		if (chrsetcmp(**input, QUOTES))
			skip_quotes(input);
		else if (**input == '(')
			skip_braces(input);
		else if (chrsetcmp(**input, "&|") && **input == *(*input + 1))
			break ;
		else
			(*input)++;
	}
	return (ft_strcut(start, *input));
}

void	assign_braces(char *raw_input, t_ctrl_seq *ctrl_seq)
{
	if (*raw_input == '(')
	{
		remove_braces(raw_input);
		ctrl_seq->inside_braces = true;
	}
	else
		ctrl_seq->inside_braces = false;
}

void	init_ctrl_seq(t_shell *mini, char *input)
{
	int			seq_count;
	int			i;

	seq_count = get_seq_count(input);
	mini->ctrl_seq = malloc(sizeof(t_ctrl_seq *) * (seq_count + 1));
	i = 0;
	while (i < seq_count)
	{
		mini->ctrl_seq[i] = malloc(sizeof(t_ctrl_seq));
		if (!mini->ctrl_seq[i])
			return ;
		mini->ctrl_seq[i]->ctrl_op = assign_ctrl_op(&input);
		mini->ctrl_seq[i]->raw_input = copy_text(&input);
		assign_braces(mini->ctrl_seq[i]->raw_input, mini->ctrl_seq[i]);
		mini->ctrl_seq[i]->cmd_seq = NULL;
		i++;
	}
	mini->ctrl_seq[i] = NULL;
}
/*
int main(void)
{
	t_ctrl_seq **ctrl_seq;
	char *input = "echo 1 && ((echo 2 || exit) && echo 3)";
	
	ctrl_seq = gen_ctrl_seq(input);

//	ft_printf("%d\n", get_seq_count(input));
	while (*ctrl_seq)
	{
		ft_printf("%s : %d\n", (*ctrl_seq)->raw_input, (*ctrl_seq)->ctrl_op);
		ctrl_seq++;
	}
}
*/