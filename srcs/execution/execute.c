/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/26 17:20:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(t_list_2 *tokenised_input)
{
	pid_t		pid;
	t_list_2	*ctrl_seq;
	t_ctrl_seq	*current;
	t_ctrl_seq	*prev;
	//int		fd[2];
	int		status;

	ctrl_seq = init_ctrl_seq(tokenised_input); // handle in main()
	while (ctrl_seq)
	{
		pid = fork();
		if (pid == 0)
		{
			current = (t_ctrl_seq *)(ctrl_seq->content);
			prev = (t_ctrl_seq *)(ctrl_seq->prev->content);
			if (current->ctrl_op == AND && prev->exit_status != 0)
				exit(-1);
			else if (current->ctrl_op == OR && prev->exit_status == 0)
				exit(-1);
			handle_redirections();
			execute_cmds(); // piping occurs here
		}
		wait(&status);
		if (WIFEXITED(status))
			current->exit_status = WEXITSTATUS(status);
		// else handle error 
		if (current->exit_status == -1)
			;// handle command execution error
	}
}
/*
int	main(void)
{
	pid_t	pid;
	int		status;
	
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		exit(13);	
	wait(&status);
	if (WIFEXITED(status))
		ft_printf("status = %d\n", WEXITSTATUS(status));
}
*/