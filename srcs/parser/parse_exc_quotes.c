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

// NOT WORKING PROPERLY

static void	skip_spaces(char *text, int *i)
{
	while(text[*i] && chrsetcmp(text[*i], SPACES))
		(*i)++;
}

static int	skip_text(char *text, int i, char *delimeter)
{
	while(text[i] && !chrsetcmp(text[i], delimeter))
		i++;
	return (i);
}

static char	*get_word(char *str, char *delimeter, int *i)
{
	int 	j;
	int		word_len;
	char	*word;

	word_len = skip_text(str, *i, delimeter) - *i;
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	j = 0;
	while (str[*i] && !chrsetcmp(str[*i], delimeter))
		word[j++] = str[(*i)++];
	word[j] = '\0';
	return (word);
}

/*
static char	*get_word(char *start)
{
	char	*end;

	end = start;
	while (*end && chrsetcmp(*end, SPACES))
	{
		if (*end == "\"")
		{
			end = strchr(start, "\"") + 1;
			continue ;
		}
		else if (*end == "\'")
		{
			end = strchr(start, "\'") + 1;
			continue ;
		}
		end++;
	}

}
*/

t_list_2	*parse_exc_quotes(char *input)
{
	int 		i;
	t_list_2	*list;
	t_word		*word;
	
	list = NULL;
	i = 0;
	skip_spaces(input, &i);
	while (input[i])
	{
		word = malloc(sizeof(t_word));
			//handle malloc error
		if (chrsetcmp(input[i], QUOTES))
		{
			if (input[i++] == '\"')
				word->token = D_QUOTES;
			else
				word->token = S_QUOTES;
			word->text = get_word(input, QUOTES, &i);
			i++;
		}
		else
			word->text = get_word(input, SPACES, &i);
		ft_lst_2add_back(&list, ft_lst_2new(word));
		skip_spaces(input, &i);
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
