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

void	execute_cmds(t_shell *mini, t_cmd_seq* command)
{
	int	i;

	if (command->pipe_count == 0)
		ft_exec(mini, (char **)command->cmds[0]); // function takes different args
	else
	{
		exec_infile_to_pipe(mini, command->pipe_fd[0], command->cmds[0]);
		i = 1;
		while (i < command->pipe_count)
		{
			exec_pipe_to_pipe(mini, command->pipe_fd[i - 1], command->pipe_fd[i], command->cmds[i]);
			i++;
		}
		exec_pipe_to_outfile(mini, command->pipe_fd[i - 1], command->cmds[i]);
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

int	exit_called(t_cmd_seq *cmd_seq)
{
	return (cmd_seq->pipe_count == 0 && ft_match(cmd_seq->cmds[0][0], "exit"));
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

int	handle_braces(t_shell *mini, t_ctrl_seq *ctrl_seq, t_dict *envp)
{
	pid_t		pid;
	int			status;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	pid = ft_fork();
	if (CHILD_PROCESS)
	{
		if (contains(ctrl_seq->raw_input, "(<>|&"))
		{
			gen_ctrl_seq(mini, ctrl_seq->raw_input);
			exit_status = execute(mini);
		}
		else
		{
			gen_cmd_seq(ctrl_seq, envp);
			if (!ctrl_seq->cmd_seq)
				exit(2);
			exit_status = exec_cmd_seq(ctrl_seq->cmd_seq, mini, false);
		}
		exit(exit_status);
	}
	wait(&status);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	return (exit_status);
}


int	execute(t_shell *mini)
{
	int			exit_status;
	int			i;

	i = 0;
	while (mini->ctrl_seq[i])
	{
		exit_status = ft_atoi(get_dict_value("?", mini->envp));
		if (ctrl_op_failure(mini->ctrl_seq[i], exit_status))
		{
			i++;
			continue ;
		}
		if (mini->ctrl_seq[i]->inside_braces)
			exit_status = handle_braces(mini, mini->ctrl_seq[i], mini->envp);
		else
		{
			gen_cmd_seq(mini->ctrl_seq[i], mini->envp);
			if (!mini->ctrl_seq[i]->cmd_seq)
				exit_status = 2;
			else
				exit_status = exec_cmd_seq(mini->ctrl_seq[i]->cmd_seq, mini, true);
		}
		set_dict_value("?", ft_itoa(exit_status), mini->envp);
		i++;
	}
	free_ctrl_seq(mini->ctrl_seq);
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