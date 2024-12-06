/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:25 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 16:24:11 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_arrlst	*parse(char *input, t_dict *envp_dict)
{
	t_arrlst	*words;
	char		*expanded_input;

	expanded_input = expand_vars(input, envp_dict, false, false);
	words = word_split(expanded_input);
	free(expanded_input);
	expand_vars_in_double_quotes(words, envp_dict);
	return (words);
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