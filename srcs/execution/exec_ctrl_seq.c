/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:50:34 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 15:10:42 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ctrl_op_failure(t_ctrl_seq *seq, int exit_status)
{
	if (seq->ctrl_op == AND && exit_status != EXIT_SUCCESS)
		return (1);
	else if (seq->ctrl_op == OR && exit_status == EXIT_SUCCESS)
		return (1);
	return (0);
}

static int	init_nested_ctrl_seq(t_shell *mini, t_ctrl_seq *ctrl_seq)
{
	int			exit_status;
	char		buf[1024];

	ft_strlcpy(buf, ctrl_seq->raw_input, 1024);
	free_ctrl_seq(mini->ctrl_seq);
	init_ctrl_seq(mini, buf);
	exit_status = exec_ctrl_seq(mini);
	return (exit_status);
}

static int	init_and_exec_cmd_seq(t_shell *mini, t_ctrl_seq *ctrl_seq)
{
	int	exit_status;

	init_cmd_seq(ctrl_seq, mini);
	if (!ctrl_seq->cmd_seq)
		exit_status = 2;
	else
		exit_status = exec_cmd_seq(ctrl_seq->cmd_seq, mini, true);
	return (exit_status);
}

static int	exec_braces(t_shell *mini, t_ctrl_seq *ctrl_seq)
{
	pid_t		pid;
	int			status;
	int			exit_status;

	exit_status = EXIT_SUCCESS;
	pid = ft_fork();
	if (pid == 0)
	{
		if (contains(ctrl_seq->raw_input, "(<>|&"))
			exit_status = init_nested_ctrl_seq(mini, ctrl_seq);
		else
			exit_status = init_and_exec_cmd_seq(mini, ctrl_seq);
		free_shell(mini);
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
			exit_status = exec_braces(mini, mini->ctrl_seq[i]);
		else
			exit_status = init_and_exec_cmd_seq(mini, mini->ctrl_seq[i]);
		set_dict_value("?", ft_itoa(exit_status), mini->envp);
		i++;
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