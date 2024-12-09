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

int	ctrl_op_success(t_ctrl_seq *seq, int exit_status)
{
	if (seq->ctrl_op == AND && exit_status == EXIT_FAILURE)
		return (0); 
	else if (seq->ctrl_op == OR && exit_status == EXIT_SUCCESS)
		return (0);
	return (1);	
}

void	execute_cmds(t_ctrl_seq* seq, t_dict *envp)
{
	int	i;

	dup2(seq->infile, STDIN_FILENO);
	dup2(seq->outfile, STDOUT_FILENO);
	if (seq->cmds->count == 1)
		ft_exec((char **)seq->cmds->content[0], envp); // handle command not found error
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

void	handle_exit_call(void **cmds)
{
	if (cmds[0] && ft_match("exit", ((char **)cmds)[0]))
		ft_exit((char **)cmds, true);
}

void	execute(t_ctrl_seq **ctrl_seq, t_dict *envp)
{
	pid_t	pid;
	int		status;
	int		exit_status;

	while (*ctrl_seq && ctrl_op_success(*ctrl_seq, exit_status))
	{
		handle_exit_call((*ctrl_seq)->cmds->content[0]);
		// cd is not working as changing inside child process
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (CHILD_PROCESS)
			execute_cmds((*ctrl_seq), envp);
		wait(&status);
		ctrl_seq++;
		if (*ctrl_seq && WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		else // process was interrupted by a signal
			break ; // ???
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