/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:00 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/05 15:41:14 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_var *new_var, t_list *envp_vars)
{
	char	*key;
	t_list	*tmp;

	tmp = envp_vars;
	while (tmp)
	{
		key = ((t_var *)(tmp)->content)->key;
		if (ft_strncmp(new_var->key, key, ft_strlen(key) + 1) == 0)
		{
			free_var(tmp->content);
			tmp->content = (void *)new_var;
			return ;
		}
		tmp = tmp->next;
	}
	ft_lstadd_back(&envp_vars, ft_lstnew((void *)new_var));
}
