/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:43:42 by mganchev          #+#    #+#             */
/*   Updated: 2025/01/06 14:21:24 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// 1st half of pattern matching
int	check_pattern(const char **pattern, const char *str, const char **wildcard,
		const char **index)
{
	while (*str)
	{
		if (**pattern == *str)
		{
			(*pattern)++;
			str++;
		}
		else if (**pattern == '*')
		{
			*wildcard = (*pattern)++;
			*index = str;
		}
		else if (*wildcard)
		{
			*pattern = *wildcard + 1;
			str = ++(*index);
		}
		else
			return (0);
	}
	return (1);
}

// 2nd half of pattern matching
int	match_pattern(const char *pattern, const char *str)
{
	const char	*wildcard;
	const char	*index;

	wildcard = NULL;
	index = NULL;
	if (str[0] == '.')
		return (0);
	if (!check_pattern(&pattern, str, &wildcard, &index))
		return (0);
	while (*pattern == '*')
	{
		pattern++;
	}
	return (*pattern == '\0');
}

// expansion of wildcard
void	expand_wildcard(t_arrlst *words, const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	char	*match;

	dir = opendir(".");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		match = ft_strdup(entry->d_name);
		if (match_pattern(pattern, entry->d_name))
			append_arrlst(words, (void *)match);
		else
			free(match);
		entry = readdir(dir);
	}
	closedir(dir);
}

/*
int	main(void)
{
	t_list	*matches;
	t_list	*temp;

	printf("Testing expand_wildcards with pattern '*.c':\n");
	matches = expand_wildcards("*****");
	temp = matches;
	while (temp)
	{
		printf("%s\n", (char *)temp->content);
		temp = temp->next;
	}
	ft_lstclear(&matches, free);
} 
*/