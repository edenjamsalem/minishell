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

static void append_redirection(t_arrlst *words, char **content)
{
	while (chrsetcmp(**content, "<>|"))
	{
		if (**content == *(*content + 1))
		{
			append_arrlst(words, ft_strcut((*content), (*content + 2)));
			*content += 2;
		}
		else 
		{
			append_arrlst(words, ft_strcut(*content, *content + 1));
			(*content)++;
		}
	}
}

static void	split_redirections(t_arrlst *words, char *content)
{
	//char	*op;
	char	*text;
	char	*file;
	char	*ptr;

	ptr = content;
	if (!chrsetcmp(*content, "<>|"))
	{
		text = ft_strcut(content, skip_to(&content, "<>|"));
		append_arrlst(words, text);
	}
	append_redirection(words, &content);
	if (*content)
	{
		file = ft_strcut(content, skip_to(&content, IFS));
		if (ft_strchrset(file, "<>|"))
		{
			split_redirections(words, file); // see if causes mem leak
			return ;
		}
		append_arrlst(words, file);
	}
	free(ptr);
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
	char		*word;
	
	list = init_arrlst(8);
		// handle malloc error
	skip_set(&input, IFS);
	while (*input)
	{
		word = get_word(&input);
		if (contains(word, "*"))
			expand_wildcard(list, word);
		else if (contains(word, "<>|"))
			split_redirections(list, word);
		else
			append_arrlst(list, word);
		skip_set(&input, IFS);
	}
	return (list);
}
/*
int main(void)
{
	char *input = "'hello''123''435'";
	t_arrlst *list = init_arrlst(4);

	if (contains_multiple_quotes(input))
		split_quotes(list, input);

	int	i = 0;
	while(list->content[i])
		ft_printf("%s\n", list->content[i++]);
}
*/