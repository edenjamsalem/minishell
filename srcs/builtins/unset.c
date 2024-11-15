/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:58:59 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 12:47:10 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_unset(t_dict *var, t_dict **envp_vars)
{
	while (envp_vars)
	{
		if (MATCH(var->key, (*envp_vars)->key))
		{
			del_dict_node(&(*envp_vars));
			return ;
		}
		(*envp_vars) = (*envp_vars)->next;
	}
}
