/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:13:18 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:13:19 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	skip_c(char const *str, char chr, int i)
{
	while (str[i] && str[i] == chr)
		i++;
	return (i);
}

static int	skip_word(char const *str, char chr, int i)
{
	while (str[i] && str[i] != chr)
		i++;
	return (i);
}

static char	*get_word(char const *str, char chr, int i)
{
	int		word_len;
	char	*word;

	word_len = (skip_word(str, chr, i) - i);
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, str + i, word_len + 1);
	return (word);
}

static int	count_words(char const *str, char chr)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	i = skip_c(str, chr, i);
	while (str[i])
	{
		i = skip_word(str, chr, i);
		count++;
		i = skip_c(str, chr, i);
	}
	return (count);
}

char	**ft_split(char const *str, char chr)
{
	int		i;
	int		j;
	int		word_count;
	char	**split_strs;

	if (!str)
		return (NULL);
	word_count = count_words(str, chr);
	split_strs = malloc(sizeof(char *) * (word_count + 1));
	if (!split_strs)
		return (NULL);
	i = 0;
	j = 0;
	i = skip_c(str, chr, i);
	while (j < word_count)
	{
		split_strs[j] = get_word(str, chr, i);
		i = skip_word(str, chr, i);
		i = skip_c(str, chr, i);
		j++;
	}
	split_strs[j] = 0;
	return (split_strs);
}
/*
#include <stdio.h>

int	main(void)
{
	int	i;
	char	**strs = ft_split("  hello my name is eden ", ' ');

	i = 0;
	while (strs[i])
	{
		printf("%s\n", strs[i]);
		i++;
	}
}
*/