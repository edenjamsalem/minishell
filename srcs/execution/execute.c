/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/04 17:22:09 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ctrl_op_success(t_ctrl_seq *seq)
{
	if (AND_FAILURE(seq) || OR_FAILURE(seq))
		return (0);
	return (1);	
}

int	builtin(char **cmd, t_dict *envp)
{
	if (ft_match(cmd[0], "env"))
		return (ft_env(envp));
	else if (ft_match(cmd[0], "cd"))
		return (ft_cd(cmd));
	else if (ft_match(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (ft_match(cmd[0], "export"))
		return (ft_export(cmd, envp));
	else if (ft_match(cmd[0], "pwd"))
		return (ft_pwd());
	else if (ft_match(cmd[0], "unset"))
		return (ft_unset(cmd, envp));
	return (0);
}

void	execute_cmds(t_ctrl_seq* seq, t_dict *envp)
{
	int	i;

	dup2(seq->infile, STDIN_FILENO);
	dup2(seq->outfile, STDOUT_FILENO);
	if (seq->cmds->count == 1)
		ft_exec(seq->cmds->content, envp); // handle command not found error
	exec_infile_to_pipe(seq->pipe_fd[0], seq->cmds->content[0], envp);
	i = 1;
	while (i < seq->cmds->count - 1)
	{
		exec_pipe_to_pipe(seq->pipe_fd, seq->cmds->content[i], i, envp);
		i++;
	}
	exec_pipe_to_outfile(seq->pipe_fd[i - 1], seq->cmds->content[i], envp);
}

void	execute(t_ctrl_seq **ctrl_seq, t_dict *envp)
{
	pid_t	pid;
	int		status;
	int		i;

	i = 0;
	// when no && or || -> dont need child process for builtin. Handle this case 
	while (ctrl_seq[i] && ctrl_op_success(ctrl_seq[i]))
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (CHILD_PROCESS)
			execute_cmds(ctrl_seq[i], envp);
		wait(&status);
		i++;
		if (ctrl_seq[i] && WIFEXITED(status))
			ctrl_seq[i]->prev_exit_status = WEXITSTATUS(status);
		else // process was interrupted by a signal
			break ; // ???
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