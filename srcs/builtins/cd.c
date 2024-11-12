/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 13:19:18 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/11 15:58:25 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_cd(char *file_path)
{
	if (!file_path || !(*file_path))
		return ;
	if (chdir(file_path) == -1)
	{
		ft_putstr_fd(2, "bash: cd: ");
		ft_putstr_fd(2, file_path);
		ft_putstr_fd(2, ": No such file or directory\n");
	}
}
