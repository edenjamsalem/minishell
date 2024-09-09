/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:19:18 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/09 14:09:50 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char *file_path)
{
	if (!file_path || !(*file_path))
		return ;
	if (chdir(file_path) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		ft_putstr_fd(file_path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
	}
}
