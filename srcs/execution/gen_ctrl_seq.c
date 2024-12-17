/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_ctrl_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 10:32:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 14:48:18 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void skip_braces(char **input)
{
	int		open_brace_count;
	int		close_brace_count;
	

	(*input)++;
	open_brace_count = 1;
	close_brace_count = 0;
	while(**input && open_brace_count > close_brace_count)
	{
		if (chrsetcmp(**input, QUOTES))
			skip_quotes(input);
		else if (**input == '(')
			open_brace_count++;
		else if (**input == ')')
			close_brace_count++;
		(*input)++;
	}
	if (open_brace_count > close_brace_count)
	{
		perror("Syntax Error: Unclosed braces");
		exit(2);
	}
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
	// check fully, this only checks first char
	return(0);
}

int	get_seq_count(char *input)
{
	int	count;

	count = 1;
	while (*(input + 1))
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == '(')
			skip_braces(&input);
		else if (chrsetcmp(*input, "&|") && *input == *(input + 1))
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
			free(input);
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
	return (NONE);
}


char	*copy_text(char **input)
{
	char	*start;

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
		(*input)++;
	}
	return (ft_strcut(start, *input));
}

void	remove_braces(char *input)
{
	char	*start;
	char	*end;

	start = input;
	end = input + ft_strlen(input) - 1;
	while (start)
	{
		if (*start == '(')
		{
			del_char(start);
			break ;
		}
		start++;
	}
	while (end)
	{
		if (*end == ')')
		{
			del_char(end);
			break ;
		}
		end--;
	}

}

bool	inside_braces(char *raw_input)
{
	return (*raw_input == '(');
}

t_ctrl_seq **gen_ctrl_seq(char *input)
{
	t_ctrl_seq	**ctrl_seq;
	int			i;

	if (ends_with_ctrl_op(input))
		input = complete_input(input);
	ctrl_seq = malloc(sizeof(t_ctrl_seq *) * (get_seq_count(input) + 1));
	i = 0;
	while (*input)
	{
		ctrl_seq[i] = malloc(sizeof(t_ctrl_seq));
		if (!ctrl_seq[i])
			return (NULL);
		ctrl_seq[i]->ctrl_op = assign_ctrl_op(&input);
		ctrl_seq[i]->raw_input = copy_text(&input);
		if (inside_braces(ctrl_seq[i]->raw_input))
		{
			ctrl_seq[i]->inside_braces = true;
			remove_braces(ctrl_seq[i]->raw_input);
		}
		i++;
	}
	ctrl_seq[i] = NULL;
	return (ctrl_seq);
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