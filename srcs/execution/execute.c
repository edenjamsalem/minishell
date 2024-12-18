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

void	execute_cmds(t_cmd_seq* command, t_dict *envp)
{
	int	i;

	if (command->pipe_count == 0)
		ft_exec((char **)command->cmds[0], envp);
	else
	{
		exec_infile_to_pipe(command->pipe_fd[0], command->cmds[0], envp);
		i = 1;
		while (i < command->pipe_count)
		{
			exec_pipe_to_pipe(command->pipe_fd[i - 1], command->pipe_fd[i], command->cmds[i], envp);
			i++;
		}
		exec_pipe_to_outfile(command->pipe_fd[i - 1], command->cmds[i], envp);
	}
}

void	reset_stdin_out(int	*stdin_out)
{
	dup2(stdin_out[0], STDIN_FILENO);
	dup2(stdin_out[1], STDOUT_FILENO);
}

void	apply_redirections(t_cmd_seq *cmd_seq, int *stdin_out)
{
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

int	exec_command(t_cmd_seq *command, t_dict* envp, bool inside_main_process)
{
	int			stdin_out[2];
	int			status;
	int			exit_status;
	pid_t		pid;

	exit_status = EXIT_SUCCESS;
	apply_redirections(command, stdin_out);
	if (command->pipe_count == 0 && is_builtin(command->cmds[0][0]))
		exit_status = exec_builtin(command->cmds[0], envp, inside_main_process);
	else
	{
		pid = ft_fork();
		if (CHILD_PROCESS)
			execute_cmds(command, envp);
		wait(&status);
		if (WIFEXITED(status))
			exit_status = WEXITSTATUS(status);
		//else // process was interrupted by a signal
		//	break ; // ???
	}
	reset_stdin_out(stdin_out);
	return (exit_status);
}

bool	contains_braces(char *input)
{
	char		*open_brace;
	char		*first_quote;
	char		*second_quote;

	open_brace = (char *)ft_strchr(input, '(');
	if (!open_brace)
		return (false);
	first_quote = ft_strchrset(input, QUOTES);
	if (!first_quote)
		return (true);
	second_quote = ft_strchrset(first_quote + 1, QUOTES);
	if(!second_quote)
		return (true);
	if (open_brace > first_quote && open_brace < second_quote)
		return (false);
	return (true);
}

int	handle_braces(t_ctrl_seq *seq, t_dict *envp)
{
	pid_t		pid;
	t_ctrl_seq	**nested_ctrl_seq;
	t_cmd_seq	*cmd_seq;
	int			status;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	pid = ft_fork();
	if (CHILD_PROCESS)
	{
		if (contains_braces(seq->raw_input) || contains_ctrl_op(seq->raw_input))
		{
			nested_ctrl_seq = gen_ctrl_seq(seq->raw_input);
			exit_status = execute(nested_ctrl_seq, envp);
		}
		else
		{
			cmd_seq = gen_cmd_seq(seq->raw_input, envp);
			exit_status = exec_command(cmd_seq, envp, false);
		}
		exit(exit_status);
	}
	wait(&status);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	//handle else case
	return (exit_status);
}

int	execute(t_ctrl_seq **ctrl_seq, t_dict *envp)
{
	int			exit_status;
	t_cmd_seq	*cmd_seq;

	while (*ctrl_seq)
	{
		exit_status = ft_atoi(get_dict_value("?", envp));
		if (ctrl_op_failure(*ctrl_seq, exit_status))
		{
			ctrl_seq++;
			continue ;
		}
		if ((*ctrl_seq)->inside_braces)
			exit_status = handle_braces(*ctrl_seq, envp);
		else
		{
			cmd_seq = gen_cmd_seq((*ctrl_seq)->raw_input, envp);
			exit_status = exec_command(cmd_seq, envp, true);
		}
		set_dict_value("?", ft_itoa(exit_status), envp);
		ctrl_seq++;
	}
	return (exit_status);
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