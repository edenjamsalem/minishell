/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:45:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/06 15:46:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_list_2 *env_vars)
{
	t_dict	*var;

	while (env_vars)
	{
		var = env_vars->content;
		printf("%s=", var->key);
		if (var->value)
			printf("%s", var->value);
		printf("\n");
		env_vars = env_vars->next;
	}
	return (1);
}
