/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/29 16:22:35 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **cmd, t_dict **envp_vars)
{
	int	i;

	i = 1;
	while (envp_vars)
	{
		if (MATCH(cmd[i], (*envp_vars)->key))
			del_dict_node(envp_vars);
		*envp_vars = (*envp_vars)->next;
	}
	return (1);
}
