/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:52:24 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/08 19:02:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	get_cmd_len(t_token *tokens)
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

static void	assign_cmds(t_cmd_seq *seq)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (i < seq->pipe_count + 1)
	{
		seq->cmds[i] = malloc(sizeof(char *) * (get_cmd_len(seq->tokens) + 2));
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

static void	init_stdin_out(t_cmd_seq *cmd_seq)
{
	cmd_seq->stdin_out = malloc(sizeof(int) * 2);
	if (!cmd_seq->stdin_out)
		return ;
	cmd_seq->stdin_out[0] = STDIN_FILENO;
	cmd_seq->stdin_out[1] = STDOUT_FILENO;
}

void	init_cmd_seq(t_ctrl_seq *ctrl_seq, t_shell *mini)
{
	ctrl_seq->cmd_seq = malloc(sizeof(t_cmd_seq));
	if (!ctrl_seq->cmd_seq)
		return ;
	parse(ctrl_seq->raw_input, ctrl_seq->cmd_seq, mini->envp);
	if (!grammar_check(ctrl_seq->cmd_seq->words, ctrl_seq->cmd_seq->tokens))
	{
		free_arrlst(ctrl_seq->cmd_seq->words, free);
		free(ctrl_seq->cmd_seq->tokens);
		free(ctrl_seq->cmd_seq);
		ctrl_seq->cmd_seq = NULL;
		return ;
	}
	quote_removal(ctrl_seq->cmd_seq->words);
	init_stdin_out(ctrl_seq->cmd_seq);
	assign_pipe_count(ctrl_seq->cmd_seq);
	setup_pipe_fd(ctrl_seq->cmd_seq);
	ctrl_seq->cmd_seq->cmds = malloc(sizeof(char **) * (ctrl_seq->cmd_seq->pipe_count + 2));
	if (!ctrl_seq->cmd_seq->cmds)
		return ;
	assign_cmds(ctrl_seq->cmd_seq);
	ctrl_seq->cmd_seq->open_fds = NULL;
	ctrl_seq->cmd_seq->open_fd_count = 0;
	assign_redirections(ctrl_seq->cmd_seq, mini);
}
