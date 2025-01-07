/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:00:09 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/07 23:53:59 by mganchev         ###   ########.fr       */
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

	(void)signum;
	mini = get_mini(NULL);
	write(STDOUT_FILENO, "\n", 1);
	if (mini->open_pipe_fd[0] != -1)
		close(mini->open_pipe_fd[0]);
	if (mini->open_pipe_fd[1] != -1)
		close(mini->open_pipe_fd[1]);
	free_shell(mini);
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
