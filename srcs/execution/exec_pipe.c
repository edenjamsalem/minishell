/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:55:07 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/09 14:34:17 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	if (pid == 0)
	{
		setup_child_handler(SIGINT);
		setup_child_handler(SIGQUIT);
	}
	return (pid);
}

pid_t	exec_infile_to_pipe(t_shell *mini, int pipe_fd[2], char **cmd)
{
	pid_t	pid;

	pid = pipe_fork(pipe_fd);
	mini->open_pipe_fd[0] = pipe_fd[0];
	mini->open_pipe_fd[1] = pipe_fd[1];
	if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
		ft_exec(mini, cmd);
	}
	close(pipe_fd[1]);
	return (pid);
}

pid_t	exec_pipe_to_pipe(t_shell *mini, int **pipe_fd, char **cmd)
{
	pid_t	pid;

	pid = pipe_fork(pipe_fd[0]);
	mini->open_pipe_fd[0] = pipe_fd[0][0];
	mini->open_pipe_fd[1] = pipe_fd[0][1];
	if (pid == 0)
	{
		close(pipe_fd[0][0]);
		dup2(pipe_fd[-1][0], STDIN_FILENO);
		dup2(pipe_fd[0][1], STDOUT_FILENO);
		close(pipe_fd[-1][0]);
		close(pipe_fd[0][1]);
		ft_exec(mini, cmd);
	}
	close(pipe_fd[0][1]);
	close(pipe_fd[-1][0]);
	return (pid);
}

pid_t	exec_pipe_to_outfile(t_shell *mini, int pipe_fd[2], char **cmd)
{
	pid_t	pid;

	pid = ft_fork();
	if (pid == 0)
	{
		mini->open_pipe_fd[0] = pipe_fd[0];
		mini->open_pipe_fd[1] = pipe_fd[1];
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		ft_exec(mini, cmd);
	}
	close(pipe_fd[0]);
	return (pid);
}

void	exec_pipes(t_shell *mini, t_cmd_seq *cmd_seq, int **pipe_fd, \
															char ***cmds)
{
	int	i;

	i = 1;
	mini->open_pids[0] = exec_infile_to_pipe(mini, pipe_fd[0], cmds[0]);
	while (i < cmd_seq->pipe_count)
	{
		mini->open_pids[i] = exec_pipe_to_pipe(mini, pipe_fd + i, cmds[i]);
		i++;
	}
	mini->open_pids[i] = exec_pipe_to_outfile(mini, pipe_fd[i - 1], cmds[i]);
	mini->open_pids[++i] = 0;
}
