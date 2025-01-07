/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:00:09 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/07 15:56:33 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

void	handle_ctrl_d(int bytes_read, int line_count, char *eof)
{
	if (bytes_read == 0)
	{
		ft_printf("\nbash: warning: here-document at line %d", line_count);
		ft_printf(" delimited by end-of-file (wanted `%s')\n", eof);
		exit(EXIT_SUCCESS);
	}
}

void	handle_ctrl_c(int signum, siginfo_t *info, void *context)
{
	(void)signum;
	(void)info;
	(void)context;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_c_child(int signum)
{
	t_shell *mini;

	mini = get_mini(NULL);
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	close(mini->open_pipe_fd);
	exit(EXIT_FAILURE);
}

void	setup_sig_handler(int signum)
{
	struct sigaction	act;

	act.sa_flags = SA_SIGINFO | SA_RESTART;
	act.sa_sigaction = handle_ctrl_c;
	sigemptyset(&act.sa_mask);
	signal(SIGQUIT, SIG_IGN);
	if (sigaction(signum, &act, NULL) == -1)
	{
		perror("Error: Signal Handler\n");
		exit(EXIT_FAILURE);
	}
}
