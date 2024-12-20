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
			init_ctrl_seq(mini, ctrl_seq->raw_input);
			exit_status = exec_ctrl_seq(mini);
		}
		else
		{
			init_cmd_seq(ctrl_seq, envp);
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

int	exec_ctrl_seq(t_shell *mini)
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
			init_cmd_seq(mini->ctrl_seq[i], mini->envp);
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