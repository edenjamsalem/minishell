/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:19:18 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:25:52 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char **cmd)
{
	if (!cmd || !(*cmd))
		return (1);
	if (ft_2darr_len((void **)cmd) > 2)
		ft_fprintf(2, "bash: cd: too many arguments\n");
	else if (chdir(cmd[1]) == -1)
		ft_perror(DIRECT, cmd[1]);
	return (EXIT_SUCCESS);
}
