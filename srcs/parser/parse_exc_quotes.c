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

static void	skip_spaces(char *text, int *i, char *spaces)
{
	while(text[*i] && chrsetcmp(text[*i], spaces))
		(*i)++;
}

static int	skip_text(char *text, int i, char *spaces)
{
	while(text[i] && !chrsetcmp(text[i], spaces))
		i++;
	return (i);
}

static char	*get_word(char *str, char *set, int *i)
{
	int 	j;
	int		word_len;
	char	*word;

	word_len = skip_text(str, *i, set) - *i;
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (str[*i] && !chrsetcmp(str[*i], set))
		word[j++] = str[(*i)++];
	return (word);
}

t_list_2	**parse_exc_quotes(char *input)
{
	int 		i;
	char		*spaces;
	char		*quotes;
	t_list_2	**list;
	t_word		*word;
	
	spaces = " \t\n";
	quotes = "\"\'";
	list = NULL;
	i = 0;
	skip_spaces(input, &i, spaces);
	while (input[i])
	{
		word = malloc(sizeof(t_word));
			//handle malloc error
		if (chrsetcmp(input[i], quotes))
			word->text = get_word(input, quotes, &i);	
		else
			word->text = get_word(input, spaces, &i);
		ft_lst_2add_back(list, ft_lst_2new(word));
		skip_spaces(input, &i, spaces);
	}
	return (list);
}

int main(void)
{
	t_list_2 **list = parse_exc_quotes("This is my \"text what should\" I do?");
	t_word *word;

	while (*list)
	{
		word = ((*list)->content);
		printf("%s\n", word->text);
		(*list) = (*list)->next;
	}
}
