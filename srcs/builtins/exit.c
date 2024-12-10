/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:33 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/10 15:54:14 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **cmd_argv, bool inside_main_process)
{
	int	len;

	len = ft_2darr_len((void **)cmd_argv);
	if (len > 2)
		perror("bash: exit: too many arguments");
	if (inside_main_process)
		ft_printf("exit\n");
	//cleanup();
	if (len == 1)
		exit(EXIT_SUCCESS);
	else
		exit(ft_atoi(cmd_argv[1]));
}