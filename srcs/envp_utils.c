/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 17:05:10 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 13:35:38 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_dict	*init_envp_dict(char **envp)
{
	int			i;
	t_dict		*node;
	t_dict		*envp_dict;

	i = 0;
	envp_dict = NULL;
	while (envp[i])
	{
		node = str_to_dict(envp[i]);
		dict_addback(&envp_dict, node);
		i++;
	}
	return (envp_dict);
}
