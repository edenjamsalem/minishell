/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_envp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 13:07:31 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/04 13:35:56 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	skip_type(char const *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '=')
		i++;
	return (i);
}

static char	*get_attr(char const *line)
{
	int		i;
	char	*attr;

	attr = malloc(sizeof(char) * ft_strlen(line) + 1);
	if (!attr)
		return (NULL);
	i = 0;
	while (line[i])
	{
		attr[i] = line[i];
		i++;
	}
	attr[i] = '\0';
	return (attr);
}

static char	*get_type(char const *line)
{
	int		i;
	int		word_len;
	char	*word;

	word_len = skip_type(line);
	word = malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '=')
	{
		word[i] = line[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**split_envp(char const *line)
{
	int		type_len;
	char	**split_line;

	if (!line)
		return (NULL);
	split_line = malloc(sizeof(char *) * (3));
	if (!split_line)
		return (NULL);
	split_line[0] = get_type(line);
	type_len = skip_type(line);
	split_line[1] = get_attr(line + type_len + 1);
	split_line[2] = 0;
	return (split_line);
}
