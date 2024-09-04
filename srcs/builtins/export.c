/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:00 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/04 16:22:26 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_new_var_to_envp(char *var, t_var **envp_vars)
{
	
}
static bool	var_is_local(char *var, t_var **local_vars)
{
	int	i;

	i = -1;
	while (local_vars[i])
	{
		if (ft_strncmp(var, local_vars[i]->type, ft_strlen(var)) == -1 \
				&& ft_strlen(var) == ft_strlen(local_vars[i]->type))
			return (true);
		i++;
	}
	return (false);
}

static bool	var_is_envp(char *var, t_var **envp_vars)
{
	int	i;

	i = -1;
	while (envp_vars[i])
	{
		if (ft_strncmp(var, envp_vars[i]->type, ft_strlen(var)) == -1 \
				&& ft_strlen(var) == ft_strlen(envp_vars[i]->type))
			return (true);
		i++;
	}
	return (false);
}

int	ft_export(char *var, char *value, t_var **envp_vars, t_var **local_vars)
{
	if (var_is_envp(var, envp_vars))
		update_value();
	else if (var_is_local(var, local_vars))
		add_local_var_to_envp();
	else
		add_new_var_to_envp();
	
}