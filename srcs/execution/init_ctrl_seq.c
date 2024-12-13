/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:52:24 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 14:53:05 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	assign_pipe_count(t_ctrl_seq *seq)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (seq->tokens[i] != END)
	{
		if (seq->tokens[i] == PIPE)
			count++;
		i++;
	}
	seq->pipe_count = count;
}


static int get_cmd_len(t_token *tokens)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tokens[i] != END && tokens[i] != PIPE)
	{
		if (tokens[i] == CMD || tokens[i] == TEXT)
			len++;
		i++;
	}
	return (len);
}

void	assign_cmds(t_ctrl_seq *seq)
{
	int		i;
	int		j;
	int		k;

	seq->cmds = malloc(sizeof(char **) * (seq->pipe_count + 2));
	if (!seq->cmds)
		return ;
	i = 0;
	k = 0;
	while (i < seq->pipe_count + 1)
	{
		seq->cmds[i] = malloc(sizeof(char *) * (get_cmd_len(seq->tokens) + 1));
		if (!seq->cmds[i])
			return ;
		j = 0;
		while (seq->tokens[k] != END && seq->tokens[k] != PIPE)
		{
			if (seq->tokens[k] == CMD || seq->tokens[k] == TEXT)
				seq->cmds[i][j++] = ft_strdup(seq->words->content[k]);
			k++;
		}
		seq->cmds[i][j] = NULL;
		if (seq->tokens[k] == PIPE)
			k++;
		i++;
	}
	seq->cmds[i] = NULL;
}

void	init_ctrl_seq(t_ctrl_seq *seq, t_dict *envp)
{
	parse(seq, envp);
	assign_redirections(seq, envp);
	assign_pipe_count(seq);
	setup_pipes(seq);
	assign_cmds(seq);
}
