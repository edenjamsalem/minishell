/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 19:02:54 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/03 14:11:14 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// set up envp dictionary
t_dict	*init_envp_dict(char **envp)
{
	int			i;
	t_dict		*node;
	t_dict		*envp_dict;

	i = 0;
	envp_dict = NULL;
	while (envp[i])
	{
		node = str_to_dict(envp[i]);
		dict_addback(&envp_dict, node);
		i++;
	}
	node = str_to_dict("?=0");
	dict_addback(&envp_dict, node);
	return (envp_dict);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*mini;

	setup_sig_handler(SIGINT);
	mini = malloc(sizeof(t_shell));
	if (!mini)
		return (NULL);
	mini->envp = init_envp_dict(envp);
	mini->ctrl_seq = NULL;
	mini->input = NULL;
	mini->stdin_out = NULL;
	return (mini);
}
