/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:22:13 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/03 12:39:02by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	reset_stdin_out(int	*stdin_out)
{
	if (stdin_out[0] != STDIN_FILENO)
	{
		dup2(stdin_out[0], STDIN_FILENO);
		close(stdin_out[0]);
	}
	if (stdin_out[1] != STDOUT_FILENO)
	{
		dup2(stdin_out[1], STDOUT_FILENO);
		close(stdin_out[1]);
	}
}

void	apply_redirections(t_cmd_seq *cmd_seq, int *stdin_out)
{
	stdin_out[0] = STDIN_FILENO;
	stdin_out[1] = STDOUT_FILENO;
	if (cmd_seq->infile != STDIN_FILENO)
	{
		stdin_out[0] = dup(STDIN_FILENO);
		dup2(cmd_seq->infile, STDIN_FILENO);
		close(cmd_seq->infile);
	}
	if (cmd_seq->outfile != STDOUT_FILENO)
	{
		stdin_out[1] = dup(STDOUT_FILENO);
		dup2(cmd_seq->outfile, STDOUT_FILENO);
		close(cmd_seq->outfile);
	}
}

int	exec_builtin(t_shell *mini, char **cmd, bool in_main)
{
	if (!cmd || !(*cmd))
		return (0);
	else if (ft_match(cmd[0], "env"))
		return (ft_env(mini->envp));
	else if (ft_match(cmd[0], "cd"))
		return (ft_cd(cmd));
	else if (ft_match(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (ft_match(cmd[0], "export"))
		return (ft_export(cmd, mini->envp));
	else if (ft_match(cmd[0], "pwd"))
		return (ft_pwd());
	else if (ft_match(cmd[0], "unset"))
		return (ft_unset(cmd, mini->envp));
	else if (ft_match(cmd[0], "exit"))
		ft_exit(mini, cmd, in_main);
	return (0);
}

void	execute_cmds(t_shell *mini, t_cmd_seq *cmd_seq)
{
	int	i;

	if (cmd_seq->pipe_count == 0)
		ft_exec(mini, (char **)cmd_seq->cmds[0]);
	else
	{
		exec_infile_to_pipe(mini, cmd_seq->pipe_fd[0], cmd_seq->cmds[0]);
		i = 1;
		while (i < cmd_seq->pipe_count)
		{
			exec_pipe_to_pipe(mini, cmd_seq->pipe_fd + i, cmd_seq->cmds[i]);
			i++;
		}
		exec_pipe_to_outfile(mini, cmd_seq->pipe_fd[i - 1], cmd_seq->cmds[i]);
	}
}

int	exec_cmd_seq(t_cmd_seq *cmd_seq, t_shell *mini, bool in_main)
{
	int			stdin_out[2];
	int			status;
	int			exit_status;
	pid_t		pid;

	exit_status = EXIT_SUCCESS;
	mini->stdin_out = stdin_out;
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
