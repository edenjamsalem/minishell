/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:01:33 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 12:18:25 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **cmd_argv)
{
	int	len;

	len = ft_2darr_len((void **)cmd_argv);
	if (len > 2)
		perror("bash: exit: too many arguments");
	else if (len == 1)
		exit(EXIT_SUCCESS);
	else 	
		exit(ft_atoi(cmd_argv[1]));
}