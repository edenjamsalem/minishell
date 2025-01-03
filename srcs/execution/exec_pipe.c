/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:38:42 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 15:43:05eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_infile_to_pipe(t_shell *mini, int pipe_fd[2], char **cmd)
{
	pid_t	pid;
	int		status;

	pid = pipe_fork(pipe_fd);
	if (CHILD_PROCESS)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		ft_exec(mini, cmd);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
}

void	exec_pipe_to_pipe(t_shell *mini, int **pipe_fd, char **cmd)
{
	pid_t	pid;
	int		status;

	pid = pipe_fork(pipe_fd[0]);
	if (CHILD_PROCESS)
	{
		close(pipe_fd[0][0]);
		dup2(pipe_fd[-1][0], STDIN_FILENO);
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		close(pipe_fd[-1][0]);
		close(pipe_fd[0][1]);
		ft_exec(mini, cmd);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[0][1]);
}

void	exec_pipe_to_outfile(t_shell *mini, int pipe_fd[2], char **cmd)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ft_exec(mini, cmd);
}
