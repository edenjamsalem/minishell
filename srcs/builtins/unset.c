/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/06 15:30:51 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_dict *var, t_list_2 **envp_vars)
{
	char		*key;
	t_list_2	*tmp;

	tmp = *envp_vars;
	while (tmp)
	{
		key = ((t_dict *)tmp->content)->key;
		if (ft_strncmp(var->key, key, ft_strlen(key) + 1) == 0)
		{
			ft_del_lst_2node(&tmp, (void (*)(void *))free_dict);
			return ;
		}
		tmp = tmp->next;
	}
}
