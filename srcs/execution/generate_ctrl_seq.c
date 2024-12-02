/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:55:29 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/28 16:326:03y eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_seq(t_ctrl_seq *ctrl_seq)
{
	ctrl_seq = malloc(sizeof(t_ctrl_seq));
	if (!ctrl_seq)
		return ;
	ctrl_seq->cmds = NULL;
	ctrl_seq->pipe_fd = NULL;
	ctrl_seq->ctrl_op = NONE;
	ctrl_seq->infile = STDIN_FILENO;
	ctrl_seq->outfile = STDOUT_FILENO;
	ctrl_seq->prev_exit_status = EXIT_SUCCESS;
}

static void	assign_ctrl_op(t_ctrl_seq *seq, char *operator)
{
	if (MATCH(operator, "&&"))
		seq->ctrl_op = AND;
	else if (MATCH(operator, "||"))
		seq->ctrl_op = OR;
}

static int	append_cmds(t_arrlst *cmds, void **input, e_token *tokens)
{
	t_arrlst	*cmd_argv;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (input[i] && tokens[i] != CTRL_OP)
	{
		cmd_argv = init_arrlst(4); // temp use to populate void **arr
		while (input[i] && tokens[i] != PIPE && tokens[i] != CTRL_OP)
		{
			if (tokens[i] != REDIRECT && tokens[i] != FILE_)
				append_arrlst(cmd_argv, input[i]);
			i++;
		}
		append_arrlst(cmds, (void *)(cmd_argv->content)); // REMEMBER TO ONLY FREE 2D ARR AS COPY OF INPUT
		free(cmd_argv); // append 2d arr and free arrlst struct
		if (input[i])
			i++;
	}
	return (i);
}

static int	get_seq_count(e_token *tokens)
{
	int	count;

	count = 0;
	while (*tokens)
	{
		if (*tokens == CTRL_OP)
			count++;
		tokens++;
	}
	return (count + 1);
}

t_ctrl_seq	**generate_ctrl_seq(void **input, e_token *tokens)
{
	t_ctrl_seq	**ctrl_seq;
	int			i;
	int			j;

	ctrl_seq = malloc(sizeof(t_ctrl_seq *) * get_seq_count(tokens) + 1);
	if (!ctrl_seq)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		init_seq(ctrl_seq[j]);
		handle_redirections(ctrl_seq[j], input + i, tokens + i);
		i += append_cmds(ctrl_seq[j]->cmds, input + i, tokens + i);
		assign_ctrl_op(ctrl_seq[j], input[i]);
		if (input[i])
			i++;
		j++;
	}
	ctrl_seq[j] = NULL;
	allocate_pipes(ctrl_seq);
	return (ctrl_seq);
}
