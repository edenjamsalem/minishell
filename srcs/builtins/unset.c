/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 15:40:43 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **cmd, t_dict *envp_vars)
{
	t_dict *start;

	start = envp_vars;
	while (*cmd)
	{
		envp_vars = start;
		while (envp_vars)
		{
			if (ft_match(*cmd, envp_vars->key))
			{
				del_dict_node(&envp_vars);
				break ;
			}
			envp_vars = envp_vars->next;
		}
		cmd++;
	}
	return (EXIT_SUCCESS);
}
