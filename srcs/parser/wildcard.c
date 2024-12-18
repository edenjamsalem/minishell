/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:43:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/18 15:23:20 by eamsalem         ###   ########.fr       */
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

// expansion of wildcard ; not sure if we need to handle the ? wildcard
t_arrlst	*expand_wildcards(const char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_arrlst			*matches;

	dir = opendir(".");
	if (!dir)
		return (NULL);
	entry = readdir(dir);
	matches = NULL;
	while (entry)
	{
		if (match_pattern(pattern, entry->d_name))
			append_arrlst(matches, (void *)entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	return (matches);
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