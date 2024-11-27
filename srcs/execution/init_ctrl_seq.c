/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:55:29 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/26 17:01:32 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_new_seq(t_ctrl_seq *ctrl_seq, char *ctrl_op)
{
	t_ctrl_seq	*new_seq;

	new_seq = malloc(sizeof(t_ctrl_seq));
	if (MATCH(ctrl_op, "&&"))
		new_seq->ctrl_op = AND;
	else if (MATCH(ctrl_op, "||"))
		new_seq->ctrl_op = OR;
	ft_lst_2add_back(&ctrl_seq, ft_lst_2new((void *)new_seq));
}

void	append_args(t_cmd *cmd, t_list_2 **input)
{
	t_list_2 *arg;
	
	while (((t_word *)((*input)->content))->token == FLAG)
	{
		arg = (((t_word *)(*input)->content))->text;
		ft_lst_2add_back(cmd->args, ft_lst_2new(arg));
		*input = (*input)->next;
	}
}

void	append_flags(t_cmd *cmd, t_list_2 **input)
{
	t_list_2 *flag;
	
	while (((t_word *)((*input)->content))->token == FLAG)
	{
		flag = (((t_word *)(*input)->content))->text;
		ft_lst_2add_back(cmd->flags, ft_lst_2new(flag));
		*input = (*input)->next;
	}
}

void	append_cmd(t_list_2 *cmds, char *cmd)
{
	t_cmd		*new_cmd;
	
	new_cmd = ft_lst_2new(malloc(sizeof(t_cmd)));
	new_cmd->cmd = cmd;
	ft_lst_2add_back(&cmds, new_cmd);
}

t_list_2	*init_ctrl_seq(t_list_2 *input)
{
	t_list_2	*ctrl_seq;
	t_list_2	*tmp;
	t_ctrl_seq	*seq;
	t_word		*word;

	ctrl_seq = ft_lst_2new(malloc(sizeof(t_ctrl_seq)));
	tmp = ctrl_seq;
	while (input)
	{
		seq = (t_ctrl_seq *)(tmp->content);
		word = (t_word *)(input->content);
		if (word->token == CMD)
		{
			append_cmd(seq->cmds, word->text);
			append_flags(seq->cmds->content, &input);
			append_args(seq->cmds->content, &input);
		}
		else if (word->token == REDIRECT)
			handle_redirections(seq, word->text);
		else if (word->token == CTRL_OP)
		{
			append_new_seq(ctrl_seq, word->text);
			tmp = tmp->next;
		}
		else
			input = input->next;
	}
	return (ctrl_seq);
}