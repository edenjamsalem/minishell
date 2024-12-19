/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:25 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/18 19:28:50 by eamsalem         ###   ########.fr       */
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