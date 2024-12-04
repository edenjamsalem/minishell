/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/12/04 15:15:51 by eamsalem         ###   ########.fr       */
=======
/*   Updated: 2024/12/04 17:22:09 by mganchev         ###   ########.fr       */
>>>>>>> github/master
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_unset(char **cmd, t_dict *envp_vars)
{
	while (envp_vars)
	{
<<<<<<< HEAD
		if (MATCH(cmd[0], envp_vars->key))
			del_dict_node(&envp_vars);
		envp_vars = envp_vars->next;
=======
		if (ft_match(cmd[i], (*envp_vars)->key))
			del_dict_node(envp_vars);
		*envp_vars = (*envp_vars)->next;
>>>>>>> github/master
	}
	return (1);
}
