/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:33:13 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/20 14:19:28 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// NEED TO MODIFY FOR MINISHELL 

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
/*
void	pipe_infile_to_cmd(int pipe_fd[2], int fd_in, char *cmd, char **envp)
{
	pid_t	pid;

	pid = pipe_fork(pipe_fd);
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(fd_in, STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_exec(cmd, envp);
	}
	close(pipe_fd[1]);
	wait(0);
}

void	pipe_cmd_to_cmd(int **pipe_fd, char **cmds, int i, char **envp)
{
	pid_t	pid;

	pid = pipe_fork(pipe_fd[i]);
	if (pid == 0)
	{
		close(pipe_fd[i][0]);
		dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		dup2(pipe_fd[i][1], STDOUT_FILENO);
		ft_exec(cmds[i], envp);
	}
	close(pipe_fd[i][1]);
	wait(0);
}

void	pipe_cmd_to_outfile(int pipe_fd[2], int fd_out, char *cmd, char **envp)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_exec(cmd, envp);
}
*/