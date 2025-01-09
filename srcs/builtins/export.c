/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:37:13 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/09 13:30:06 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	valid_identifier(char *key)
{
	while (*key && *key != '=')
	{
		if (!ft_isalnum(*key))
		{
			ft_perror(IDENTIFIER, key);
			return (0);
		}
		key++;
	}
	return (1);
}

void	export_new_entry(char *cmd, t_dict *envp)
{
	t_dict	*new_entry;
	t_dict	*entry_exists;
	
	new_entry = str_to_dict(cmd);
	entry_exists = get_dict_entry(new_entry->key, envp);
	if (!new_entry->value)
		free_dict(new_entry);
	else if (!entry_exists)
		dict_addback(&envp, new_entry);
	else
	{
		free(entry_exists->value);
		entry_exists->value = ft_strdup(new_entry->value);
		free_dict(new_entry);
	}
}

int	ft_export(char **cmd, t_dict *envp)
{
	int		i;

	i = 1;
	while (cmd[i])
	{
		if (valid_identifier(cmd[i]))
			export_new_entry(cmd[i], envp);
		i++;
	}
	return (EXIT_SUCCESS);
}
