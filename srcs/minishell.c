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

int	ctrl_op_syntax_okay(char *input)
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
	t_shell		*mini;

	(void)argc;
	(void)argv;
	mini = init_shell(envp);
	if (!mini)
		exit(2);
	while (1)
	{
		setup_sig_handler(SIGINT);
	//	mini->input = read_input();
		mini->input = ft_strdup("echo $? && dwqdwq || echo $? && exit");
		if (!mini->input)
			continue ;
		if (ends_with_ctrl_op(mini->input))
			mini->input = complete_input(mini->input);
		if (ctrl_op_syntax_okay(mini->input))
		{
			init_ctrl_seq(mini, mini->input);
			exec_ctrl_seq(mini);
			free_ctrl_seq(mini->ctrl_seq);
		}
		free(mini->input);
		break ;
	}
}
