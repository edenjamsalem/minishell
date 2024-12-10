/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 12:45:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/10 17:29:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_dict *envp_vars)
{
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