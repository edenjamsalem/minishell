/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:33 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 14:19:21 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **cmd_argv, bool inside_pipe)
{
	int	len;

	len = ft_2darr_len((void **)cmd_argv);
	if (len > 2)
		perror("bash: exit: too many arguments");
	else if (len == 1)
	{
		//cleanup();
		if (!inside_pipe)
			ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		//cleanup(); 	
		if (!inside_pipe)
			ft_printf("exit\n");
		exit(ft_atoi(cmd_argv[1]));
	}
}