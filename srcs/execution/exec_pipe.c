/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:33:13 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 18:18:25by eamsalem         ###   ########.fr       */
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
		ft_exec(mini, cmd);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
}

void	exec_pipe_to_pipe(t_shell *mini, int *prev_pipe_fd, int *pipe_fd, char **cmd)
{
	pid_t	pid;
	int		status;

	pid = pipe_fork(pipe_fd);
	if (CHILD_PROCESS)
	{
		close(pipe_fd[0]);
		dup2(prev_pipe_fd[0], STDIN_FILENO);
		dup2(pipe_fd[1], STDOUT_FILENO);
		ft_exec(mini, cmd);
	}
	waitpid(pid, &status, 0);
	close(pipe_fd[1]);
}

void	exec_pipe_to_outfile(t_shell *mini, int pipe_fd[2], char **cmd)
{
	dup2(pipe_fd[0], STDIN_FILENO);
	close(pipe_fd[0]);
	ft_exec(mini, cmd);
}
