/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:37:13 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 15:37:18 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export(char **cmd, t_dict *envp_vars)
{
	t_dict	*new_entry;
	t_dict	*entry_exists;
	int		i;

	i = 1;
	while (cmd[i])
	{
		new_entry = str_to_dict(cmd[i]);
		entry_exists = get_dict_entry(new_entry->key, envp_vars);
		if (!new_entry->value)
			free_dict(new_entry);
		else if (!entry_exists)
			dict_addback(&envp_vars, new_entry);
		else
		{
			free(entry_exists->value);
			entry_exists->value = ft_strdup(new_entry->value);
			free_dict(new_entry);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
