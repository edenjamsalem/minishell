/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:24:59 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/02 16:25:34 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	append_redirection(t_arrlst *words, char **content)
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

static void	split_redirections(t_arrlst *list, char *word)
{
	char	*text;
	char	*file;
	char	*ptr;

	ptr = word;
	if (!chrsetcmp(*word, "<>|"))
	{
		text = ft_strcut(word, skip_to(&word, "<>|"));
		append_arrlst(list, text);
	}
	append_redirection(list, &word);
	if (*word)
	{
		file = ft_strcut(word, skip_to(&word, IFS));
		if (contains(file, "<>|"))
		{
			split_redirections(list, file);
			free(ptr);
			return ;
		}
		append_arrlst(list, file);
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
	if (!list)
		return (NULL);
	skip_set(&input, IFS);
	while (*input)
	{
		word = get_word(&input);
		if (contains(word, "*"))
		{
			expand_wildcard(list, word);
			free(word);
		}
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