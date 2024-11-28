/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:55:29 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/28 12:39:24 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	append_new_seq(t_arrlst *ctrl_seq, char *ctrl_op)
{
	t_ctrl_seq	*new_seq;

	new_seq = malloc(sizeof(t_ctrl_seq));
	if (MATCH(ctrl_op, "none"))
		new_seq->ctrl_op = NONE;
	else if (MATCH(ctrl_op, "&&"))
		new_seq->ctrl_op = AND;
	else if (MATCH(ctrl_op, "||"))
		new_seq->ctrl_op = OR;
	append_arrlst(ctrl_seq, new_seq);
}

void	append_cmd(t_arrlst *cmds, char *cmd)
{

}

t_list_2	*init_ctrl_seq(t_arrlst *ctrl_seq, t_arrlst *input)
{
	t_ctrl_seq	*current_seq;
	t_word		*word;
	int			i;
	int			j;

	init_arrlst(ctrl_seq, 4);
	append_new_seq(ctrl_seq, "none");
	i = 0;
	j = 0;
	while (i < input->count)
	{
		current_seq = (t_ctrl_seq *)(ctrl_seq->content[j]);
		word = (t_word *)((input)->content[i]);
		if (word->token == CMD)
			append_cmd(current_seq->cmds, input->content[i]);
		else if (word->token == REDIRECT)
			handle_redirections(current_seq, );
		else if (word->token == CTRL_OP)
		{
			append_new_seq(ctrl_seq, word->text);
			j++;
		}
		i++;
	}
	return (ctrl_seq);
}