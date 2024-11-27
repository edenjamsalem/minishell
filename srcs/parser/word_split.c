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

// HAS SIGSEGV FAULT, FIND WHY !!!

void	split_ctrl_ops(char *content, t_list_2 **list)
{
	t_word	*op;
	t_word	*text;
	t_word	*file;

	if (!chrsetcmp(*content, "<>|&"))
	{
		text = malloc(sizeof(t_word));
		text->text = ft_strcut(content, skip_to(&content, "<>|&"));
		ft_lst_2add_back(list, ft_lst_2new(text));
	}
	op = malloc(sizeof(t_word));
	op->text = ft_strcut(content, skip_set(&content, "<>|&"));
	ft_lst_2add_back(list, ft_lst_2new(op));
	if (*content)
	{
		file = malloc(sizeof(t_word));
		file->text = ft_strcut(content, skip_to(&content, IFS));
		ft_lst_2add_back(list, ft_lst_2new(file));
	}
}

bool	check_for_op(char *content)
{
	char		*first_op;
	char		*first_quote;

	first_op = ft_strchrset(content, "<>|&");
	if (!first_op)
		return (false);
	first_quote = ft_strchrset(content, QUOTES);
	if (!first_quote)
		return (true);
	if(first_op > first_quote)
		return (false);
	return (true);
}

static char	*get_word(char **input)
{
	char	*start;

	start = *input;
	while (**input && !chrsetcmp(**input, IFS))
	{
		if (chrsetcmp(**input, QUOTES))
			skip_quotes(input);
		else
			(*input)++;
	}
	return (ft_strcut(start, *input));
}

t_list_2	*word_split(char *input)
{
	t_list_2	*list;
	char		*content;
	t_word		*word;
	
	list = NULL;
	skip_set(&input, IFS);
	while (*input)
	{
		content = get_word(&input);
		if (check_for_op(content))
		{
			split_ctrl_ops(content, &list);
			free(content);
		}
		else
		{
			word = malloc(sizeof(t_word));
			if (!word)
				return NULL;
			word->text = content;
			ft_lst_2add_back(&list, ft_lst_2new(word));
		}
		skip_set(&input, IFS);
	}
	return (list);
}
/*
int main(void)
{
	t_list_2 *list = word_split("This	is my\"text what\" should\'>>\'");
	t_list_2 *tmp;

	tmp = list;
	while (tmp)
	{
		ft_printf("%s\n", ((t_word *)tmp->content)->text);
		tmp = tmp->next;
	}
	ft_lst_2clear(&list, (void *)free_word);
	free(list);
}
*/