/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/05 16:49:40 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_var *var, t_list_2 *envp_vars)
{
	char		*key;
	t_list_2	*tmp;

	tmp = envp_vars;
	while (tmp)
	{
		key = ((t_var *)(tmp)->content)->key;
		if (ft_strncmp(var->key, key, ft_strlen(key) + 1) == 0)
		{
			free_var(tmp->content);
			tmp->content = (void *)var;
			return ;
		}
		tmp = tmp->next;
	}
	// NEED 2 WAY LINKED LISTS TO DELETE NODE MIDWAY THROUGH LIST
}
