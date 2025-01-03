/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:21:03 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 15:52:33 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	setup_pipe_fd(t_cmd_seq *cmd_seq)
{
	int	i;

	cmd_seq->pipe_fd = NULL;
	if (cmd_seq->pipe_count == 0)
		return ;
	cmd_seq->pipe_fd = malloc(sizeof(int *) * (cmd_seq->pipe_count + 1));
	if (!cmd_seq->pipe_fd)
		return ;
	i = 0;
	while (i < cmd_seq->pipe_count)
	{
		cmd_seq->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!cmd_seq->pipe_fd[i])
		{
			free_2darr((void *)cmd_seq->pipe_fd, i - 1);
			return ;
		}
		i++;
	}
	cmd_seq->pipe_fd[i] = NULL;
}
