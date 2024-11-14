/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:00 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 12:34:40 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_export(t_dict *new_var, t_dict **envp_vars)
{
	t_dict	*var;

	var = get_dict_entry(new_var->key, *envp_vars);
	if (!var)
		dict_addback(envp_vars, new_var);
	else
	{
		var->value = new_var->value;
		free_dict(new_var);
	}
}
