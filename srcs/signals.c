/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:00:09 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/10 20:26:13 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	g_signal = signum;
	if (g_signal == SIGINT) // handles ctrl+C
		write(STDOUT_FILENO, "\nminishell > ", 13);
	else if (g_signal == EOF) // handles ctrl+D
		exit(EXIT_FAILURE); // execve handles cat special case
}

void	setup_sig_handlers(void)
{
	struct sigaction act;

	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = handle_signal;
	sigemptyset(&act.sa_mask);
	if (sigaction(SIGINT, &act, NULL) == -1)
	{
		perror("Error: Signal Handler\n");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGQUIT, &act, NULL) == -1)
	{
		perror("Error: Signal Handler\n");
		exit(EXIT_FAILURE);
	}
}
