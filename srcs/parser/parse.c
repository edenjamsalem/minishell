/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:25 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 14:27:44 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void	parse(t_ctrl_seq *seq, t_dict *envp_dict)
{
	char		*expanded_input;

	expanded_input = expand_vars(seq->raw_input, envp_dict, false, false);
	seq->words = word_split(expanded_input);
	free(expanded_input);
	expand_vars_in_double_quotes(seq->words, envp_dict);
	seq->tokens = tokenise(seq->words);
	if (!grammar_check(seq->words, seq->tokens))
	{
	//	set_dict_value("?", ft_itoa(2), envp);
	//	free_mem();
	}
	quote_removal(seq->words);
}
/*
int	main(int argc, char **argv, char **envp)
{
	char		*input = " This is my \"\'$SHELL\'\" \'hello\' what>>\'isyours? $";
	t_arrlst	*parsed_input;
	t_dict		*envp_dict;
	int			i = 0;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	parsed_input = parse(input, envp_dict);
	while (i < parsed_input->count)
	{
		printf("%s\n", (char *)parsed_input->content[i]);
		i++;
	}
	dict_clear(&envp_dict);
	free_arrlst(parsed_input, free);
	free(parsed_input);
}
*/