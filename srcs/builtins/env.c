/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:45:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/04 15:43:06 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_var **env_vars)
{
	int	i;

	i = 0;
	while (env_vars[i])
	{
		printf("%s=%s\n", env_vars[i]->type, env_vars[i]->value);
		i++;
	}
	return (1);
}
