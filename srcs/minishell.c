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

t_signal	g_signal = {0, 0}; // struct holding signals

// read input, add history and handling signals
char	*read_input(void)
{
	char *input;
	char prompt[100];

	if (!g_signal.prompt_printed)
	{
		getcwd(prompt, sizeof(prompt));
		ft_strlcat(prompt, " > ", 100);
		input = readline(prompt);
		g_signal.prompt_printed = 0;
	}
	else
		input = readline("");
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
		if (g_signal.signal) // means a message is being received	
		{
			g_signal.signal = 0;
			g_signal.prompt_printed = 1;
		}	
		input = read_input();
		if (!input)
			continue ;
		ctrl_seq = gen_ctrl_seq(input);
		execute(ctrl_seq, envp_dict);
		free(input);
	}
	cleanup(envp_dict);
}
