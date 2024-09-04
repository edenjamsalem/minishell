/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/04 16:33:02 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_var	**parse_envp(char **envp)
{
	int		i;
	char	**line;
	t_var	**envp_vars;

	envp_vars = malloc(sizeof(t_var *) * (ft_2darr_len((void *)envp) + 1));
	i = 0;
	while (envp[i])
	{
		line = split_envp(envp[i]);
		envp_vars[i] = malloc(sizeof(t_var));
		envp_vars[i]->type = line[0];
		envp_vars[i]->value = line[1];
		free(line);
		i++;
	}
	envp_vars[i] = NULL;
	return (envp_vars);
}

void	free_envp_vars(t_var **envp_vars)
{
	int	i;

	i = 0;
	while (envp_vars[i])
	{
		free(envp_vars[i]->type);
		free(envp_vars[i]->value);
		free(envp_vars[i]);
		i++;
	}
	free(envp_vars);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_var	**envp_vars;
//	t_var	**local_vars;
	int		i;

	//init_signal_handler 
	(void)argc;
	(void)argv;
//	init_local_vars(local_vars);
	envp_vars = parse_envp(envp);
	i = 0;
	while (i < 1)
	{
		input = readline("minishell >  ");
		if (ft_strncmp(input, "env", 4) == 0)
			ft_env(envp_vars);
		else if (ft_strncmp(input, "pwd", 4) == 0)
			ft_pwd();
		free(input);
		i++;
	}
	free_envp_vars(envp_vars);
}
