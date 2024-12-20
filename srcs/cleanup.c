/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:52:01 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 14:52:55 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_cmd_seq(t_cmd_seq *cmd_seq)
{
	int		i;
	char	**cmds;

	if (!cmd_seq)
		return ;
	i = 0;
	while (cmd_seq->cmds[i])
	{
		cmds = cmd_seq->cmds[i];
		free_2darr((void **)cmds, ft_2darr_len((void **)cmds));
		i++;
	}
	free(cmd_seq->cmds);
	free_2darr((void **)cmd_seq->pipe_fd, ft_2darr_len((void**)cmd_seq->pipe_fd));
	free_arrlst(cmd_seq->words, free);
	free(cmd_seq->tokens);
	free(cmd_seq);
}

void	free_ctrl_seq(t_ctrl_seq **ctrl_seq)
{
	int	i;

	i = 0;
	while (ctrl_seq[i])
	{
		free(ctrl_seq[i]->raw_input);
		free_cmd_seq(ctrl_seq[i]->cmd_seq);
		free(ctrl_seq[i]);
		i++;
	}
	free(ctrl_seq);
}

void	free_shell(t_shell *mini)
{
	rl_clear_history();
	free_dict(mini->envp);
	free_ctrl_seq(mini->ctrl_seq);
	free(mini);
}
