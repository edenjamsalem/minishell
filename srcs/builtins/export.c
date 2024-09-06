/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:00 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/06 15:08:07 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_dict *new_var, t_list_2 *envp_vars)
{
	char		*var;
	t_list_2	*tmp;

	tmp = envp_vars;
	while (tmp)
	{
		var = ((t_dict *)(tmp)->content)->key;
		if (ft_strncmp(new_var->key, var, ft_strlen(var) + 1) == 0)
		{
			free_dict(tmp->content);
			tmp->content = (void *)new_var;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lst_2add_back(&envp_vars, ft_lst_2new((void *)new_var));
}
