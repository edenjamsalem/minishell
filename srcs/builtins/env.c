/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:45:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 19:29:52 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_env(char **cmd, t_dict *envp_vars)
{
	if (ft_2darr_len((void **)cmd) > 1)
	{
		ft_perror(DIRECT, cmd[1]);
		return (127);
	}
	print_dict(envp_vars);
	return (EXIT_SUCCESS);
}
/*
int main(int argc, char **argv, char **envp)
{
	t_dict *envp_dict = init_envp_dict(envp);

	print_dict(envp_dict);
}
*/