/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:13:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/09 17:44:29by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ctrl_op_failure(t_ctrl_seq *seq, int exit_status)
{
	if (seq->ctrl_op == AND && exit_status != EXIT_SUCCESS)
		return (1); 
	else if (seq->ctrl_op == OR && exit_status == EXIT_SUCCESS)
		return (1);
	return (0);	
}

void	execute_cmds(t_ctrl_seq* seq, t_dict *envp)
{
	int	i;

	if (seq->pipe_count == 0)
		ft_exec((char **)seq->cmds[0], envp);
	else
	{
		exec_infile_to_pipe(seq->pipe_fd[0], seq->cmds[0], envp);
		i = 1;
		while (i < seq->pipe_count)
		{
			exec_pipe_to_pipe(seq->pipe_fd, seq->cmds[i], i, envp);
			i++;
		}
		exec_pipe_to_outfile(seq->pipe_fd[i - 1], seq->cmds[i], envp);
	}
}

void	dup_stdin_out(int *stdin_out)
{
	stdin_out[0] = dup(STDIN_FILENO);
	stdin_out[1] = dup(STDOUT_FILENO);
}

void	reset_stdin_out(int	*stdin_out)
{
	dup2(stdin_out[0], STDIN_FILENO);
	dup2(stdin_out[1], STDOUT_FILENO);
}

void	execute(t_ctrl_seq **ctrl_seq, t_dict *envp)
{
	pid_t		pid;
	int			status;
	int			stdin_out[2];
	int			exit_status = EXIT_SUCCESS;

	while (*ctrl_seq)
	{
		if (ctrl_op_failure(*ctrl_seq, exit_status))
		{
			ctrl_seq++;
			continue ;
		}
		dup_stdin_out(stdin_out);
		init_ctrl_seq(*ctrl_seq, envp);
		if ((*ctrl_seq)->pipe_count == 0 && is_builtin((*ctrl_seq)->cmds[0]))
			exit_status = exec_builtin((*ctrl_seq)->cmds[0], envp, true);
		else
		{
			pid = ft_fork();
			if (CHILD_PROCESS)
				execute_cmds(*ctrl_seq, envp);
			wait(&status);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else // process was interrupted by a signal
				break ; // ???
		}
		reset_stdin_out(stdin_out);
		ctrl_seq++;
	}
}

/*
int main(int argc, char **argv, char **envp)
{
	char		*input = "exit";
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

	i = 0;
	while (i < words->count)
	{
		ft_printf("%s:%d\n", words->content[i], tokens[i]);
		i++;
	}
	ctrl_seq = generate_ctrl_seq(words, tokens);
	execute(ctrl_seq, envp_dict);
	dict_clear(&envp_dict);
	free_arrlst(words, free);
	free(words);
}

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