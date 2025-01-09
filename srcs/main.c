/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:53:57 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/09 15:06:38 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_shell(t_shell *mini)
{
	if (ends_with_ctrl_op(mini->input))
		mini->input = complete_input(mini->input);
	if (ctrl_op_syntax_okay(mini->input))
	{
		init_ctrl_seq(mini, mini->input);
		exec_ctrl_seq(mini);
		free_ctrl_seq(mini->ctrl_seq);
		mini->ctrl_seq = NULL;
	}
	else
		set_dict_value("?", ft_strdup("2"), mini->envp);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell		*mini;

	(void)argc;
	(void)argv;
	mini = init_shell(envp);
	if (!mini)
		exit(2);
	while (1)
	{
		setup_sig_handler(SIGINT);
		mini->input = read_input();
		if (!mini->input)
			continue ;
		run_shell(mini);
		free(mini->input);
		mini->input = NULL;
	}
}
