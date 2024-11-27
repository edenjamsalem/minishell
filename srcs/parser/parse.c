/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:25 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/27 18:50:36 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_word(t_word *word)
{
	free(word->text);
	free(word);
}

t_arrlst	*parse(char *input, t_dict *envp_dict)
{
	t_arrlst	*words;
	char		*expanded_input;

	expanded_input = expand_vars(input, envp_dict, IGNORE_QUOTED_VARS);
	words = word_split(expanded_input);
	free(expanded_input);
//	tokenise_quotes();
	expand_vars_inside_quotes(words, envp_dict);
	quote_removal(words);
//	tokenise(words);
	return (words);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input = " This is my \"$LANGUAGE\"\'hello\' what>>\'isyours? $";
	t_arrlst	*parsed_input;
	t_dict		*envp_dict;
	int			i = 0;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	parsed_input = parse(input, envp_dict);
	while (i < parsed_input->capacity)
	{
		printf("%s\n", ((t_word *)parsed_input->content[i])->text);
		i++;
	}
	dict_clear(&envp_dict);
	free_arrlst(parsed_input, (void *)free_word);
	free(parsed_input);
}
