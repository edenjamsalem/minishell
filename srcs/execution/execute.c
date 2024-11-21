/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/21 14:18:33 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute(t_shell *mini)
{
	pid_t	pid;
	t_cmd	*cmd;
	int		fd[2];
	int		status;
	
	while (mini->cmds)
	{
		pid = fork();
		if (pid = 0)
		{
			cmd = ((t_list_2 *)(mini->cmds))->content;
			if (cmd->condition == AND && mini->exit_status != 0)
				exit(-1);
			else if (cmd->condition == OR && mini->exit_status == 0)
				exit(-1);
			handle_redirections(mini->input, mini->pipe_fd); // need to handle independently for each condtional op
			exec_cmd(); // Any piping will happen here 
		}
		wait(&status);
		if (WIFEXITED(status))
			mini->exit_status = WEXITSTATUS(status);
		// else handle error 
		if (mini->exit_status == -1)
			// handle command execution error
	}
}

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
