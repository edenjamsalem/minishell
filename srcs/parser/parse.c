/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:25 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 16:10:58 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse(char *input, t_cmd_seq *cmd_seq, t_dict *envp)
{
	char		*expanded_input;

	expanded_input = expand_vars(input, envp, false, false);
	cmd_seq->words = word_split(expanded_input);
	free(expanded_input);
	expand_vars_in_double_quotes(cmd_seq->words->content, envp);
	cmd_seq->tokens = tokenise(cmd_seq->words);
}
