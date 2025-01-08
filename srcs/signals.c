/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:00:09 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/08 20:19:33 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>

void	handle_ctrl_d(int line_count, char *eof)
{
	ft_printf("\nbash: warning: here-document at line %d", line_count);
	ft_printf(" delimited by end-of-file (wanted `%s')\n", eof);
	free_shell(get_mini(NULL));
	exit(EXIT_SUCCESS);
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

void	handle_ctrl_c_child(int signum, siginfo_t *info, void *context)
{
	t_shell	*mini;

	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		mini = get_mini(NULL);
		write(STDOUT_FILENO, "\n", 1);
		if (mini->open_pipe_fd[0] != -1)
			close(mini->open_pipe_fd[0]);
		if (mini->open_pipe_fd[1] != -1)
			close(mini->open_pipe_fd[1]);
		free_shell(mini);
		exit(EXIT_FAILURE);
	}
}

void	setup_child_handler(int signum)
{
	struct sigaction	act;
	struct termios		term;

	if (signum == SIGQUIT)
	{
		act.sa_handler = SIG_IGN;
		act.sa_flags = 0;
		tcgetattr(STDIN_FILENO, &term);
		term.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	else if (signum == SIGINT)
	{
		act.sa_flags = SA_SIGINFO | SA_RESTART;
		act.sa_sigaction = handle_ctrl_c_child;
	}
	sigemptyset(&act.sa_mask);
	if (sigaction(signum, &act, NULL) == -1)
	{
		perror("Error: Child Signal Handler\n");
		exit(EXIT_FAILURE);
	}
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
