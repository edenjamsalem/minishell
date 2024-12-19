/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:33 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/19 17:37:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	get_exit_status(char **cmd_argv, int len)
{
	if (len < 2)
		return (EXIT_SUCCESS);
	return (ft_atoi(cmd_argv[1]));
}


void	ft_exit(t_shell *mini, char **cmd_argv, bool inside_main_process)
{
	int	len;
	int	exit_status;

	if (!cmd_argv || !(*cmd_argv))
		return ;
	len = ft_2darr_len((void **)cmd_argv);
	if (len > 2)
		perror("bash: exit: too many arguments");
	exit_status = get_exit_status(cmd_argv, len);
	if (inside_main_process)
	{
		free_shell(mini);
		ft_printf("exit\n");
	}
	exit(exit_status);
}