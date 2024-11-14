/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 18:16:51 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


volatile sig_atomic_t	g_flag = 0; // signal receiving flag

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	char		**args;
	t_dict		*envp_dict;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	setup_sig_handlers(); // initialise signal handlers first;
	while (1)
	{
		if (g_flag) // means a message is being received
			{	
				g_flag = 0; // reset flag
				free(input);
				input = readline("minishell > "); // reset prompt
				continue ;
			}
		input = readline("minishell > ");
		if (!input) // handling EOF / ctrl + D
		{
			ft_printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		
	//	parse(input);
		
		args = ft_split(input, ' ');
		if (ft_strncmp(args[0], "env", 4) == 0)
			ft_env(envp_dict);
		else if (ft_strncmp(args[0], "pwd", 4) == 0)
			ft_pwd();
		else if (ft_strncmp(args[0], "cd", 3) == 0)
			ft_cd(args[1]);
		else if (ft_strncmp(args[0], "export", 7) == 0)
			ft_export(str_to_dict(args[1]), &envp_dict);
		else if (ft_strncmp(args[0], "unset", 6) == 0)
			ft_unset(str_to_dict(args[1]), &envp_dict);
		else if (ft_strncmp(args[0], "exit", 4) == 0)
		{
			free_2darr((void *)args, ft_2darr_len((void *)args));
			free(input);
			break ;
		}
		free_2darr((void *)args, ft_2darr_len((void *)args));
		free(input);
	}
	rl_clear_history();
	dict_clear(&envp_dict);
}
