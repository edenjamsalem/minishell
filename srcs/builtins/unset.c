/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/04 17:22:09 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **cmd, t_dict **envp_vars)
{
	int	i;

	i = 1;
	while (envp_vars)
	{
		if (ft_match(cmd[i], (*envp_vars)->key))
			del_dict_node(envp_vars);
		*envp_vars = (*envp_vars)->next;
	}
	return (1);
}
