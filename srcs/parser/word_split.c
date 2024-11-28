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

static void	split_ctrl_ops(t_arrlst *list, char *content)
{
	char	*op;
	char	*text;
	char	*file;
	char	*ptr;

	ptr = content;
	if (!chrsetcmp(*content, "<>|&"))
	{
		text = ft_strcut(content, skip_to(&content, "<>|&"));
		append_arrlst(list, text);
	}
	op = ft_strcut(content, skip_set(&content, "<>|&"));
	append_arrlst(list, op);
	if (*content)
	{
		file = ft_strcut(content, skip_to(&content, IFS));
		append_arrlst(list, file);
	}
	free(ptr);
}

static bool	check_for_ctrl_op(char *content)
{
	char		*op;
	char		*first_quote;
	char		*second_quote;

	op = ft_strchrset(content, "<>|&");
	if (!op)
		return (false);
	first_quote = ft_strchrset(content, QUOTES);
	if (!first_quote)
		return (true);
	second_quote = ft_strchrset(first_quote + 1, QUOTES);
	if(!second_quote)
		return (true);
	if (op > first_quote && op < second_quote)
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

t_arrlst	*word_split(char *input)
{
	t_arrlst	*list;
	char		*content;
	
	list = malloc(sizeof(t_arrlst));
	if (!list)
		return (NULL);
	init_arrlst(list, 8);
	skip_set(&input, IFS);
	while (*input)
	{
		content = get_word(&input);
		if (check_for_ctrl_op(content))
			split_ctrl_ops(list, content);
		else
			append_arrlst(list, content);
		skip_set(&input, IFS);
	}
	return (list);
}
/*
int main(void)
{
	t_list_2 *list = word_split(" This is my \"$PATH\" what>>\'isyours? $");
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