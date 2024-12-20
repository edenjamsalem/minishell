/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:22:13 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 18:55:03 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	execute_cmds(t_shell *mini, t_cmd_seq* cmd_seq)
{
	int	i;

	if (cmd_seq->pipe_count == 0)
		ft_exec(mini, (char **)cmd_seq->cmds[0]); // function takes different args
	else
	{
		exec_infile_to_pipe(mini, cmd_seq->pipe_fd[0], cmd_seq->cmds[0]);
		i = 1;
		while (i < cmd_seq->pipe_count)
		{
			exec_pipe_to_pipe(mini, cmd_seq->pipe_fd[i - 1], cmd_seq->pipe_fd[i], cmd_seq->cmds[i]);
			i++;
		}
		exec_pipe_to_outfile(mini, cmd_seq->pipe_fd[i - 1], cmd_seq->cmds[i]);
	}
}

void	reset_stdin_out(int	*stdin_out)
{
	if (stdin_out[0] != STDIN_FILENO)
		dup2(stdin_out[0], STDIN_FILENO);
	if (stdin_out[1] != STDOUT_FILENO)
		dup2(stdin_out[1], STDOUT_FILENO);
}

void	apply_redirections(t_cmd_seq *cmd_seq, int *stdin_out)
{
	stdin_out[0] = STDIN_FILENO;
	stdin_out[1] = STDOUT_FILENO;
	if (cmd_seq->infile != STDIN_FILENO)
	{
		stdin_out[0] = dup(STDIN_FILENO);
		dup2(cmd_seq->infile, STDIN_FILENO);
	}
	if (cmd_seq->outfile != STDOUT_FILENO)
	{
		stdin_out[1] = dup(STDOUT_FILENO);
		dup2(cmd_seq->outfile, STDOUT_FILENO);
	}	
}

int	exec_cmd_seq(t_cmd_seq *cmd_seq, t_shell *mini, bool in_main)
{
	int			stdin_out[2];
	int			status;
	int			exit_status;
	pid_t		pid;

	exit_status = EXIT_SUCCESS;
	apply_redirections(cmd_seq, stdin_out);
	if (cmd_seq->pipe_count == 0 && is_builtin(cmd_seq->cmds[0][0]))
		exit_status = exec_builtin(mini, cmd_seq->cmds[0], in_main);
	else
	{
		pid = ft_fork();
		if (CHILD_PROCESS)
			execute_cmds(mini, cmd_seq);
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
	}
	reset_stdin_out(stdin_out);
	return (exit_status);
}