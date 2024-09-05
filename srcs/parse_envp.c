/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_envp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:07:31 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/04 13:35:56 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_type(char const *envp_line)
{
	int	i;

	i = 0;
	while (envp_line[i] && envp_line[i] != '=')
		i++;
	return (i);
}

static char	*get_value(char const *envp_line)
{
	int		i;
	char	*value;

	value = malloc(sizeof(char) * ft_strlen(envp_line) + 1);
	if (!value)
		return (NULL);
	i = 0;
	while (envp_line[i])
	{
		value[i] = envp_line[i];
		i++;
	}
	value[i] = '\0';
	return (value);
}

static char	*get_type(char const *envp_line)
{
	int		i;
	int		type_len;
	char	*type;

	type_len = skip_type(envp_line);
	type = malloc(sizeof(char) * (type_len + 1));
	if (!type)
		return (NULL);
	i = 0;
	while (envp_line[i] && envp_line[i] != '=')
	{
		type[i] = envp_line[i];
		i++;
	}
	type[i] = '\0';
	return (type);
}

// THIS FUNCTION SPLITS A LINE FROM THE ENVP INTO ITS VAR-TYPE AND VALUE

t_var	*parse_envp(char const *envp_line)
{
	t_var	*var;
	int		value_index;

	var = malloc(sizeof(t_var));
	if (!envp_line)
		return (NULL); // think about if i need this 
	var->key = get_type(envp_line);
	value_index = skip_type(envp_line) + 1;
	var->value = get_value(envp_line + value_index);
	return (var);
}
