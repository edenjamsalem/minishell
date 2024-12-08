/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:33:13 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 12:19:16 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

pid_t	pipe_fork(int pipe_fd[2])
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	return (pid);
}

void	exec_infile_to_pipe(int pipe_fd[2], char **cmd, t_dict *envp)
{
	pid_t	pid;
	int		status;

	pid = pipe_fork(pipe_fd);
	if (CHILD_PROCESS)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_exec(cmd, envp);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
}

void	exec_pipe_to_pipe(int **pipe_fd, char **cmd, int i, t_dict *envp)
{
	pid_t	pid;
	int		status;

	pid = pipe_fork(pipe_fd[i]);
	if (CHILD_PROCESS)
	{
		close(pipe_fd[i][0]);
		dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		dup2(pipe_fd[i][1], STDOUT_FILENO);
		ft_exec(cmd, envp);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[i][1]);
}

void	exec_pipe_to_outfile(int pipe_fd[2], char **cmd, t_dict *envp)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ft_exec(cmd, envp);
}
