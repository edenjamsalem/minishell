/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/05 15:00:28 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_envp_vars(char **envp, t_list **envp_vars)
{
	int		i;
	t_var	*var;

	i = 0;
	while (envp[i])
	{
		var = parse_envp(envp[i]);
		ft_lstadd_back(envp_vars, ft_lstnew((void *)var));
		i++;
	}
}

void	free_var(t_var *var)
{
	free(var->key);
	free(var->value);
	free(var);
}

void	free_envp_vars(t_list *envp_vars)
{
	t_list	*tmp;

	while (envp_vars)
	{
		tmp = envp_vars->next;
		free_var(envp_vars->content);
		free(envp_vars);
		envp_vars = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**line;
	t_list	*envp_vars;

	(void)argc;
	(void)argv;
	//init_signal_handler 
	envp_vars = NULL;
	init_envp_vars(envp, &envp_vars);
	while (1)
	{
		input = readline("minishell >  ");
		line = ft_split(input, ' ');
		if (ft_strncmp(line[0], "env", 4) == 0)
			ft_env(envp_vars);
		else if (ft_strncmp(line[0], "pwd", 4) == 0)
			ft_pwd();
		else if (ft_strncmp(line[0], "export", 7) == 0)
			ft_export(parse_envp(line[1]), envp_vars);
		free(input);
	}
	free_envp_vars(envp_vars);
}
