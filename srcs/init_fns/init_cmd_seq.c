/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:52:24 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 16:53:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	assign_pipe_count(t_cmd_seq *command)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (command->tokens[i] != END)
	{
		if (command->tokens[i] == PIPE)
			count++;
		i++;
	}
	command->pipe_count = count;
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

void	assign_cmds(t_cmd_seq *cmd_seq)
{
	int		i;
	int		j;
	int		k;

	cmd_seq->cmds = malloc(sizeof(char **) * (cmd_seq->pipe_count + 2));
	if (!cmd_seq->cmds)
		return ;
	i = 0;
	k = 0;
	while (i < cmd_seq->pipe_count + 1)
	{
		cmd_seq->cmds[i] = malloc(sizeof(char *) * (get_cmd_len(cmd_seq->tokens) + 1));
		if (!cmd_seq->cmds[i])
			return ;
		j = 0;
		while (cmd_seq->tokens[k] != END && cmd_seq->tokens[k] != PIPE)
		{
			if (cmd_seq->tokens[k] == CMD || cmd_seq->tokens[k] == TEXT)
				cmd_seq->cmds[i][j++] = ft_strdup(cmd_seq->words->content[k]);
			k++;
		}
		cmd_seq->cmds[i][j] = NULL;
		if (cmd_seq->tokens[k] == PIPE)
			k++;
		i++;
	}
	cmd_seq->cmds[i] = NULL;
}

void	init_cmd_seq(t_ctrl_seq *ctrl_seq, t_dict *envp)
{
	t_cmd_seq *cmd_seq;

	cmd_seq = malloc(sizeof(t_cmd_seq));
	if (!cmd_seq)
		return ;
	parse(ctrl_seq->raw_input, cmd_seq, envp);
	if (!grammar_check(cmd_seq->words, cmd_seq->tokens))
	{
		free_arrlst(cmd_seq->words, free);
		free(cmd_seq->tokens);
		return ;
	}
	quote_removal(cmd_seq->words);
	assign_redirections(cmd_seq, envp);
	assign_pipe_count(cmd_seq);
	setup_pipes(cmd_seq);
	assign_cmds(cmd_seq);
	ctrl_seq->cmd_seq = cmd_seq;
}
