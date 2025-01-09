/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:54:57 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/09 14:05:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_stdin_out(int	*stdin_out)
{
	if (!stdin_out)
		return ;
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

void	apply_redirections(t_cmd_seq *cmd_seq)
{
	if (cmd_seq->infile != STDIN_FILENO)
	{
		cmd_seq->stdin_out[0] = dup(STDIN_FILENO);
		dup2(cmd_seq->infile, STDIN_FILENO);
		close(cmd_seq->infile);
	}
	if (cmd_seq->outfile != STDOUT_FILENO)
	{
		cmd_seq->stdin_out[1] = dup(STDOUT_FILENO);
		dup2(cmd_seq->outfile, STDOUT_FILENO);
		close(cmd_seq->outfile);
	}
}

int	exec_builtin(t_shell *mini, char **cmd, bool in_main)
{
	if (!cmd || !(*cmd))
		return (0);
	else if (ft_match(cmd[0], "env"))
		return (ft_env(cmd, mini->envp));
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

void	wait_for_pids(t_shell *mini)
{
	int		i;
	
	i = 0;
	while (mini->open_pids[i])
		wait(mini->open_pids + i++);
	free_shell(mini);
	exit(EXIT_SUCCESS);
}

void	execute_cmds(t_shell *mini, t_cmd_seq *cmd_seq)
{
	int		i;

	if (cmd_seq->pipe_count == 0)
		ft_exec(mini, (char **)cmd_seq->cmds[0]);
	else
	{
		mini->open_pids = malloc(sizeof(pid_t) * (cmd_seq->pipe_count + 2));
		if (!mini->open_pids)
		{
			free_shell;
			exit(EXIT_FAILURE);
		}	
		mini->open_pids[0] = exec_infile_to_pipe(mini, cmd_seq->pipe_fd[0], cmd_seq->cmds[0]);
		i = 1;
		while (i < cmd_seq->pipe_count)
		{
			mini->open_pids[i] = exec_pipe_to_pipe(mini, cmd_seq->pipe_fd + i, cmd_seq->cmds[i]);
			i++;
		}
		mini->open_pids[i] = exec_pipe_to_outfile(mini, cmd_seq->pipe_fd[i - 1], cmd_seq->cmds[i]);
		mini->open_pids[++i] = 0;
		wait_for_pids(mini);
	}
}

int	exec_cmd_seq(t_cmd_seq *cmd_seq, t_shell *mini, bool in_main)
{
	int			status;
	int			exit_status;
	pid_t		pid;

	if (!cmd_seq->cmds[0][0])
		return (EXIT_SUCCESS);
	apply_redirections(cmd_seq);
	if (cmd_seq->pipe_count == 0 && is_builtin(cmd_seq->cmds[0][0]))
		exit_status = exec_builtin(mini, cmd_seq->cmds[0], in_main);
	else
	{
		pid = ft_fork();
		if (pid == 0)
			execute_cmds(mini, cmd_seq);
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else
			exit_status = EXIT_FAILURE;
	}
	reset_stdin_out(cmd_seq->stdin_out);
	return (exit_status);
}
