/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 13:10:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/12 15:09:55by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_word(char **input)
{
	char	*start;

	start = *input;
	while (**input && !chrsetcmp(**input, SPACES))
	{
		if (**input == '\"')
			skip_quotes(input, '\"');
		else if (**input == '\'')
			skip_quotes(input, '\'');
		else
			(*input)++;
	}
	return (ft_strcut(start, *input));
}


t_list_2	*word_split(char *input)
{
	t_list_2	*list;
	t_word		*word;
	
	list = NULL;
	skip_spaces(&input);
	while (*input)
	{
		word = malloc(sizeof(t_word));
			//malloc error
		word->text = get_word(&input);
		ft_lst_2add_back(&list, ft_lst_2new(word));
		skip_spaces(&input);
	}
	return (list);
}

void	free_word(t_word *word)
{
	free(word->text);
	free(word);
}
/*
int main(void)
{
	t_list_2 *list = word_split("This is my\"text what\" \"\' shouldI do?");
	t_list_2 *tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s\n", ((t_word *)tmp->content)->text);
		tmp = tmp->next;
	}
	ft_lst_2clear(&list, (void *)free_word);
	free(list);
}
*/