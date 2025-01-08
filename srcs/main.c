/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:53:57 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 17:48:08 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		if (ends_with_ctrl_op(mini->input))
			mini->input = complete_input(mini->input);
		if (ctrl_op_syntax_okay(mini->input))
		{
			init_ctrl_seq(mini, mini->input);
			exec_ctrl_seq(mini);
			free_ctrl_seq(mini->ctrl_seq);
		}
		else
			set_dict_value("?", ft_strdup("2"), mini->envp);
		free(mini->input);
	}
}
