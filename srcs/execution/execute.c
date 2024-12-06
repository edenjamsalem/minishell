/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 10:47:19 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ctrl_op_success(t_ctrl_seq *seq)
{
	if (seq->ctrl_op == AND && seq->prev_exit_status == EXIT_FAILURE)
		return (0); 
	else if (seq->ctrl_op == OR && seq->prev_exit_status == EXIT_SUCCESS)
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
	{
		ft_exec((char **)seq->cmds->content[0], envp); // handle command not found error
	}
	else
	{
		exec_infile_to_pipe(seq->pipe_fd[0], (char **)seq->cmds->content[0], envp);
		i = 1;
		while (i < seq->cmds->count - 1)
		{
			exec_pipe_to_pipe(seq->pipe_fd, (char **)seq->cmds->content[i], i, envp);
			i++;
		}
		exec_pipe_to_outfile(seq->pipe_fd[i - 1], (char **)seq->cmds->content[i], envp);
	}
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

int main(int argc, char **argv, char **envp)
{
	char		*input = "head -n 5 file1 && tail -n 2 file1";
	t_dict		*envp_dict = init_envp_dict(envp);
	t_arrlst	*words;
	t_token 	*tokens; 
	t_ctrl_seq	**ctrl_seq;
	int			i;
	int			j;
	int			k;

	(void)argc;
	(void)argv;
	words = parse(input, envp_dict);
	tokens = tokenise(words);
	quote_removal(words);

/*	i = 0;
	while (i < words->count)
	{
		ft_printf("%s:%d\n", words->content[i], tokens[i]);
		i++;
	}*/
	ctrl_seq = generate_ctrl_seq(words, tokens);
	execute(ctrl_seq, envp_dict);
	dict_clear(&envp_dict);
	free_arrlst(words, free);
	free(words);
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