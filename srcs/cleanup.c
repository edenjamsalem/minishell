/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:52:01 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/30 16:10:12 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_perror(t_error type, char *error_msg)
{
    if (type == SYNTAX)
    {
        ft_fprintf(2, "syntax error near unexpected token '%s'\n", error_msg);
        return (0);
    }
    else if (type == CMD_)
    {
        ft_fprintf(2, "'%s': command not found\n", error_msg);
        return (0);
    }
    else if (type == DIRECT)
    {
        ft_fprintf(2, "'%s': No such file or directory\n", error_msg); 
        return (0);
    }
    return (1);
}

void	close_open_fds(int *open_fds, int fd_count)
{
	int	i;
	
	i = 0;
	while (i < fd_count)
	{
		close((open_fds[i]));	
		i++;
	}
}

void	free_cmd_seq(t_cmd_seq *cmd_seq)
{
	char	**cmds;
	int		i;

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
	close_open_fds(cmd_seq->open_fds, cmd_seq->open_fd_count);
	free(cmd_seq->open_fds);
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
	dict_clear(&mini->envp);
	free_ctrl_seq(mini->ctrl_seq);
	free(mini);
}
