/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:32:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 11:42:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_ctrl_seq	*init_seq()
{
	// TESTED
	t_ctrl_seq *seq;

	seq = malloc(sizeof(t_ctrl_seq));
	if (!seq)
		return (NULL);
	seq->cmds = init_arrlst(2);
	if (!seq->cmds)
		return (NULL); // handle freeing properly
	seq->pipe_fd = NULL;
	seq->ctrl_op = NONE;
	seq->infile = STDIN_FILENO;
	seq->outfile = STDOUT_FILENO;
	return (seq);
}

int ends_with_ctrl_op(char *input)
{
	int	end;

	if (!input)
		return (0);
	end = ft_strlen(input) - 1;
	while (end > 2 && chrsetcmp(input[end], IFS))
		end--;
	if (input[end] == '|' || (input[end] == '&' && input[end - 1] == '&'))
		return (1);
	return (0);
}

int	syntax_error(char *text)
{
	while (chrsetcmp(*text, IFS))
		text++;
	if (chrsetcmp(*text, "&|"))
		return (1);
	// check fully
	return(0);
}

int	get_seq_count(char *input)
{
	int	count;

	count = 1;
	while (*(input + 1))
	{
		if (chrsetcmp(*input, "&|") && *input == *(input + 1))
			count++;
		input++; 
	}
	return (count);
}

char	*complete_input(char *input)
{
	char	buf[4096];
	char	tmp[1024];
	int		bytes_read;
	
	ft_strlcpy(buf, input, 4096);
	while (ends_with_ctrl_op(buf))
	{
		write(1, "> ", 2);
		bytes_read = read(STDIN_FILENO, tmp, 1024);
		tmp[bytes_read - 1] = '\0';
		if (syntax_error(tmp))
		{
			ft_perror(SYNTAX, tmp); // need to cut just token not whole str
		//	free(input);
			exit(2);
		}
		ft_strlcat(buf, tmp, 4096);
	}
//	free(input);
	return (ft_strdup(buf));
}

t_ctrl_op assign_ctrl_op(char **input)
{
	char ctrl_op[3];

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
	return (PIPE_);
}

char	*copy_text(char **input)
{
	char	*start;
	char	*completed;

	start = *input;
	while (**input)
	{
		if (chrsetcmp(**input, QUOTES))
			skip_quotes(input);
		else if (chrsetcmp(**input, "&|") && **input == *(*input + 1))
			break ;
		(*input)++;
	}
	return (ft_strcut(start, *input));
}

t_ctrl_seq **split_ctrl_op(char *input)
{
	t_ctrl_seq	**ctrl_seq;
	int			i;

	input = complete_input(input);
	ctrl_seq = malloc(sizeof(t_ctrl_seq *) * (get_seq_count(input) + 1));
	i = 0;
	while (*input)
	{
		ctrl_seq[i] = init_seq();
		ctrl_seq[i]->ctrl_op = assign_ctrl_op(&input);
		ctrl_seq[i]->raw_input = copy_text(&input);
		ft_printf("%s\n", ctrl_seq[i]->raw_input);
		i++;
	}
	ctrl_seq[i] = NULL;
	return (ctrl_seq);
}

int main(void)
{
	t_ctrl_seq **ctrl_seq;
	
	ctrl_seq = split_ctrl_op("Hello \"&& my\" name || is  ede &&");
	while (*ctrl_seq)
	{
		ft_printf("%s : %d\n", (*ctrl_seq)->raw_input, (*ctrl_seq)->ctrl_op);
		ctrl_seq++;
	}
}