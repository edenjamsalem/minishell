/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/06 13:46:34 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// USE THE DEL FUNCTION PROTOTYPE AS GIVEN IN LIBFT TO MAKE FREEING NODES EASIER
// CREATE A DEL FUNCTION THAT CAN DELETE A MIDWAY NODE IN A 2WAY LINKED LIST

void	init_envp_vars(char **envp, t_list_2 **envp_vars)
{
	int		i;
	t_dict	*var;

	i = 0;
	while (envp[i])
	{
		var = str_to_dict(envp[i]);
		ft_lst_2add_back(envp_vars, ft_lst_2new((void *)var));
		i++;
	}
}

void	free_envp_vars(t_list_2 *envp_vars)
{
	t_list_2	*tmp;

	while (envp_vars)
	{
		tmp = envp_vars->next;
		free_dict(envp_vars->content);
		free(envp_vars);
		envp_vars = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**line;
	t_list_2	*envp_vars;

	(void)argc;
	(void)argv;
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
			ft_export(str_to_dict(line[1]), envp_vars);
		else if (ft_strncmp(line[0], "unset", 6) == 0)
			ft_unset(str_to_dict(line[1]), &envp_vars);
		else if (ft_strncmp(line[0], "exit", 4) == 0)
		{
			free_2darr((void *)line, ft_2darr_len((void *)line));
			free(input);
			break ;
		}
		free_2darr((void *)line, ft_2darr_len((void *)line));
		free(input);
	}
	free_envp_vars(envp_vars);
}
