/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:28 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 15:36:47 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **cmd)
{
	bool	n_flag;
	int		i;

	if (ft_2darr_len((void **)cmd) < 2)
	{
		ft_printf("\n");
		return (EXIT_SUCCESS);
	}
	n_flag = false;
	i = 1;
	if (ft_match(cmd[1], "-n"))
	{
		n_flag = true;
		i++;
	}
	while (cmd[i])
		ft_printf("%s ", cmd[i++]);
	if (!n_flag)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
