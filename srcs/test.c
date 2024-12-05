/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 17:01:31 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/05 17:06:31 by eamsalem         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_dict		*envp_dict;
	char	**my_envp;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	my_envp = dict_to_arr(envp_dict);
	int i = 0;
	while (my_envp[i])
	{
		ft_printf("%s\n", my_envp[i++]);
	}	
}