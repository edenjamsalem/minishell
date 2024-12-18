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

// clean up function
void	cleanup(t_dict *envp_dict)
{
	rl_clear_history();
	dict_clear(&envp_dict);
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
			skip_quotes(&input);
		else if (*input == '(')
			open_brace_count++;
		else if (*input == ')')
			close_brace_count++;
		input++;
	}
	if (open_brace_count == close_brace_count)
		return (1);
	ft_fprintf(2, "bash: syntax error: incorrect braces\n");
	return (0);
}

int	braces_next_to_ctrl_ops(char *input)
{
	char *next_word;

	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == ')' && *(++input) && *input != ')')
		{
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

int	ctrl_ops_okay(char *input)
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
			if (chrsetcmp(*input, "|&"))
			{
				next_word = ft_strcut(input, skip_to(&input, IFS));
				ft_perror(SYNTAX, next_word);
				free(next_word);
				return (0);
			}	
		}
		input++;
	}
	return (1);
}

int	ctrl_syntax_okay(char *input)
{
	if (!brace_count_same(input))
		return (0);
	if (!braces_next_to_ctrl_ops(input))
		return (0);
	if (!ctrl_ops_okay(input))
		return (0);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_dict		*envp_dict;
	t_ctrl_seq	**ctrl_seq;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	rl_catch_signals = 0;
	setup_sig_handler(SIGINT); // initialise signal handlers first;
	while (1)
	{
		//setup_sig_handler(SIGINT);
		input = read_input();
		if (!input)
			continue ;
		if (ctrl_syntax_okay(input))
		{
			ctrl_seq = gen_ctrl_seq(input);
			execute(ctrl_seq, envp_dict);
		}
		free(input);
	}
	cleanup(envp_dict);
}
