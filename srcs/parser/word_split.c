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

static void append_ctrl_op(t_arrlst *list, char **content)
{
	while (chrsetcmp(**content, "<>|&"))
	{
		if (**content == *(*content + 1))
		{
			append_arrlst(list, ft_strcut((*content), (*content + 2)));
			*content += 2;
		}
		else 
		{
			append_arrlst(list, ft_strcut(*content, *content + 1));
			(*content)++;
		}
	}
}

static void	split_ctrl_ops(t_arrlst *list, char *content)
{
	//char	*op;
	char	*text;
	char	*file;
	char	*ptr;

	ptr = content;
	if (!chrsetcmp(*content, "<>|&"))
	{
		text = ft_strcut(content, skip_to(&content, "<>|&"));
		append_arrlst(list, text);
	}
	append_ctrl_op(list, &content);
	if (*content)
	{
		file = ft_strcut(content, skip_to(&content, IFS));
		if (ft_strchrset(file, "<>|&"))
		{
			split_ctrl_ops(list, file); // see if causes mem leak
			return ;
		}
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
	
	list = init_arrlst(8);
		// handle malloc error
	for (int i = 0; i <= 8; i++) // need to initialise individual members of list, can't add it to init_arrlst bc it's in libft
		list->content[i] = NULL;
	skip_set(&input, IFS);
	while (*input)
	{
		content = get_word(&input);
		if (check_for_ctrl_op(content)) // also need to split ctrl ops
			split_ctrl_ops(list, content); // split any bunched up redirection
		else
			append_arrlst(list, content);
		skip_set(&input, IFS);
	}
	return (list);
}
/*
int main(void)
{
	t_arrlst *list = word_split(" This is my \"$PATH\" what>>&|&||\'isyours? $");
	int	i = 0;

	while (i < list->count)
	{
		ft_printf("%s\n", list->content[i]);
		i++;
	}
	free_arrlst(list, free);
	free(list);
}
*/