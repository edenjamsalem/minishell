/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/06 12:43:35 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_dict *var, t_list_2 **envp_vars)
{
	char		*key;

	while (envp_vars)
	{
		key = ((t_dict *)(*envp_vars)->content)->key;
		if (ft_strncmp(var->key, key, ft_strlen(key) + 1) == 0)
		{
			ft_del_lst_2node(envp_vars, (void (*)(void *))free_dict);
			return ;
		}
		*envp_vars = (*envp_vars)->next;
	}
}
