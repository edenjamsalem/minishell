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

static void	skip_spaces(char **text)
{
	while(**text && chrsetcmp(**text, SPACES))
		(*text)++;
}

static void skip_quotes(char **text, char quote)
{
	char	*closing_quote;

	closing_quote = (char *)ft_strchr(*text + 1, quote);
	if (closing_quote)
		(*text) = closing_quote + 1;
	else {
		(*text)++;
	}
}

static char	*cut_word(char *start, char *end)
{
	char 	*text;
	char 	*start;
	t_word	*word;

	text = malloc(sizeof(char) * (end - start + 1));
		//malloc error
	start = text;
	while (start < end)
		*text++ = *start++;
	*text = '\0';
	return (start);
}

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
	return (cut_word(start, *input));
}


t_list_2	*parse_exc_quotes(char *input)
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
/*
int main(void)
{
	t_list_2 *list = parse_exc_quotes("This is my\"text what\" \"\' shouldI do?");

	while (list)
	{
		printf("%s\n", ((t_word *)list->content)->text);
		list = list->next;
	}
}
*/