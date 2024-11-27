/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:16:25 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/27 14:44:48 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_word(t_word *word)
{
	free(word->text);
	free(word);
}

t_list_2	*parse(char *input, t_dict *envp_dict)
{
	t_list_2	*words;
	char		*expanded_input;
	
	expanded_input = expand_vars(input, envp_dict, IGNORE_QUOTED_VARS);
	words = word_split(expanded_input);
//	tokenise_quotes();
	expand_vars_inside_quotes(words, envp_dict);
	quote_removal(words);
//	tokenise(words);
	free(expanded_input);
	return (words);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input = " This is my \"$PATH\" \'what>>isyours?\' $";
	t_list_2	*parsed_input;
	t_list_2	*tmp;
	t_dict		*envp_dict;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	parsed_input = parse(input, envp_dict);
	tmp = parsed_input;
	while (tmp)
	{
		printf("%s\n", ((t_word *)tmp->content)->text);
		tmp = tmp->next;
	}
	dict_clear(&envp_dict);
	ft_lst_2clear(&parsed_input, (void *)free_word);
}
