/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:00:09 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/14 18:19:49 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <signal.h>

void handle_signal(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT) // handles ctrl+C
	{
		g_flag = 1;
		write(STDOUT_FILENO, "\nminishell > ", 13);
		// end process inside shell and display prompt
	}
	else if (signum == EOF) // handles ctrl+D
		exit(EXIT_FAILURE); // need to implement case where cat is used
}
// come back and check for sigquit

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

