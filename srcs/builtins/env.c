/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:45:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/22 10:19:59 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_dict *envp_vars)
{
	while (envp_vars)
	{
		ft_printf("%s=", envp_vars->key);
		if (envp_vars->value)
			ft_printf("%s", envp_vars->value);
		ft_printf("\n");
		envp_vars = envp_vars->next;
	}
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	t_dict *envp_dict = init_envp_dict(envp);

	print_dict(envp_dict);
}