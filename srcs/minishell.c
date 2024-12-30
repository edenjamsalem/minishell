/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 12:22:47by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // initialise
// // set up signal handlers
// // parse input
// tokenise parsed input > skip quotes when checking for PIPE, CTRL OP and REDIRECT
// // quote removal
// // set up control seq
// // execute
// free

// read input, add history and handling signals
char	*read_input(void)
{
	char *input;
	char prompt[100];

	getcwd(prompt, sizeof(prompt));
	ft_strlcat(prompt, " > ", 100);
	input = readline(prompt);
	if (!input) // handling EOF / ctrl + D
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	else
	{
		free(input); // handles ENTER key press
		return (NULL);
	}
	return (input);
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

char	*complete_input(char *input)
{
	char	buf[4096];
	char	line[1024];
	int		bytes_read;
	
	ft_strlcpy(buf, input, 4096);
	while (ends_with_ctrl_op(buf))
	{
		write(1, "> ", 2);
		bytes_read = read(STDIN_FILENO, line, 1024);
		line[bytes_read - 1] = '\0';
		ft_strlcat(buf, line, 4096);
	}
	free(input);
	return (ft_strdup(buf));
}

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
			continue;
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
	char *next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == ')' && *(input + 1) && *(input + 1) != ')')
		{
			input++;
			skip_set(&input, IFS);
			if (!chrsetcmp(*input, "<>&|"))
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
	char *next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == '(' && *(input + 1) && *(input + 1) != '(')
		{
			input++;
			skip_set(&input, IFS);
			if (chrsetcmp(*input, "<>&|"))
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
	char *next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
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
	char *next_word;

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

int	ctrl_syntax_okay(char *input)
{
	if (first_word_ctrl_op(input))
		return (0);
	if (!brace_count_same(input))
		return (0);
	if (!ctrl_op_after_close_brace(input))
		return (0);
	if (ctrl_op_after_open_brace(input))
		return (0);
	if (ctrl_ops_adjacent(input))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_shell		*mini;

	(void)argc;
	(void)argv;
	mini = init_shell(envp);
	if (!mini)
		exit(2);
	while (1)
	{
		setup_sig_handler(SIGINT);
	//	input = read_input();
		input = "((echo 123) && echo 456) && exit";
		if (!input)
			continue ;
		if (ends_with_ctrl_op(input))
			input = complete_input(input);
		if (ctrl_syntax_okay(input))
		{
			init_ctrl_seq(mini, input);
		//	free(input);
			exec_ctrl_seq(mini);
		}
		free_ctrl_seq(mini->ctrl_seq);
	}
}
