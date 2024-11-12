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

static char	*copy_word(char *letter, char *end)
{
	char 	*text;
	char 	*start;
	t_word	*word;

	text = malloc(sizeof(char) * (end - letter + 1));
		//malloc error
	start = text;
	while (letter < end)
		*text++ = *letter++;
	*text = '\0';
	return (start);
}

static char	*get_word(char **current)
{
	char	*start;

	start = *current;
	while (**current && !chrsetcmp(**current, SPACES))
	{
		if (**current == '\"')
			*current = (char *)ft_strchr(*current + 1, '\"') + 1;
		else if (**current == '\'')
			*current = (char *)ft_strchr(*current + 1, '\'') + 1;
		else
			(*current)++;
	}
	return (copy_word(start, *current));
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

int main(void)
{
	t_list_2 *list = parse_exc_quotes("This is my \"text what should\"I do?");

	while (list)
	{
		printf("%s\n", ((t_word *)list->content)->text);
		list = list->next;
	}
}
