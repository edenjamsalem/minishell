/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:28 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/05 17:25:18 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **cmd)
{
	bool	n_flag;
	int		i;
	
	if (ft_2darr_len((void **)cmd) < 2)
		ft_printf("\n");
	i = 1;
	n_flag = false;
	if (ft_match(cmd[1], "-n"))
	{
		n_flag = true;
		i++;
	}
	while (cmd[i])
		ft_printf("%s ", cmd[i++]);
	if (!n_flag)
		ft_printf("\n");
	return (1);
}
