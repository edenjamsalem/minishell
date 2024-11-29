/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/29 17:19:40 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_single_cmd(char **cmd, t_dict *envp)
{
	pid_t pid;

	if (builtin(cmd, envp))
		return ;
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			ft_exec(cmd, envp); // handle command not found error
		wait(0);
	}
}

void	handle_exit_status(int status, t_ctrl_seq *seq)
{
	if (WIFEXITED(status))
		seq->exit_status = WEXITSTATUS(status);
	// else handle error 
	
	if (seq->exit_status == EXIT_FAILURE)
		;// handle command execution error
}

void	execute_cmds(t_ctrl_seq* seq, t_dict *envp)
{
	int	i;

	if (seq->cmds->count == 1)
	{
		exec_single_cmd(seq->cmds->content, envp);
		return ;
	}
	exec_infile_to_pipe(seq->pipe_fd[0], seq->infile, seq->cmds->content[0], envp);
	i = 1;
	while (i < seq->cmds->count - 1)
	{
		exec_pipe_to_pipe(seq->pipe_fd, seq->cmds->content[i], i, envp);
		i++;
	}
	exec_pipe_to_outfile(seq->pipe_fd[i - 1], seq->outfile, seq->cmds->content[i], envp);
}

void	execute(t_ctrl_seq **ctrl_seq, t_dict *envp)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	while (ctrl_seq[i])
	{
		if (ctrl_seq[i]->condition == AND && ctrl_seq[i]->exit_status == EXIT_FAILURE)
			break ;
		else if (ctrl_seq[i]->condition == OR && ctrl_seq[i]->exit_status == EXIT_SUCCESS)
			break ;
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			dup2(ctrl_seq[i]->infile, STDIN_FILENO);
			dup2(ctrl_seq[i]->outfile, STDOUT_FILENO);
			execute_cmds(ctrl_seq[i], envp); // piping occurs here
		}
		i++;
		wait(&status);
		handle_exit_status(status, ctrl_seq[i]);
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