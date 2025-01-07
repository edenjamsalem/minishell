/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 16:26:17 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/07 16:45:52 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	single_quotes_inside_double(char *input)
{
	char	*open_double;
	char	*close_double;
	char	*open_single;
	char	*close_single;

	open_single = (char *)ft_strchr(input, '\'');
	open_double = (char *)ft_strchr(input, '"');
	if (!open_single || !open_double)
		return (0);
	close_single = (char *)ft_strchr(open_double + 1, '\'');
	close_double = (char *)ft_strchr(open_double + 1, '"');
	if (open_double < open_single && close_double > close_single)
		return (1);
	return (0);
}

static void	copy_quoted_text(char **input, char **expanded)
{
	char	*closing_quote;

	if (!(*input) || !(*expanded))
		return ;
	closing_quote = (char *)ft_strchr(*input + 1, **input);
	if (closing_quote)
	{
		ft_strlcpy(*expanded, *input, (closing_quote - *input + 2));
		skip_quotes(input);
		skip_quotes(expanded);
	}
	else
		*(*expanded)++ = *(*input)++;
}

static void	copy_expanded_var(char **input, char **expanded, t_dict *envp)
{
	char	*key;
	char	*value;

	if (**input == '?')
	{
		value = get_dict_value("?", envp);
		(*input)++;
	}
	else
	{
		key = ft_strcut(*input, skip_while(input, ft_isalnum));
		value = get_dict_value(key, envp);
		free(key);
	}
	if (value)
	{
		ft_strlcpy(*expanded, value, ft_strlen(value) + 1);
		skip_len(expanded, ft_strlen(value));
	}
}

char	*expand_vars(char *input, t_dict *envp, bool in_double, bool in_single)
{
	char	expanded[2048];
	char	*ptr;

	if (single_quotes_inside_double(input))
		in_single = true;
	ptr = expanded;
	while (*input)
	{
		if (*input == '\'' && !in_single)
			copy_quoted_text(&input, &ptr);
		else if (*input == '\"' && !in_double)
			copy_quoted_text(&input, &ptr);
		else if (*input == '$' && *(input + 1) && !chrsetcmp(*(input + 1), IFS))
			copy_expanded_var(&input, &ptr, envp);
		*ptr++ = *input++;
	}
	*ptr = '\0';
	return (ft_strdup(expanded));
}

void	expand_vars_in_double_quotes(void **input, t_dict *envp_dict)
{
	char	*expanded;
	int		i;

	i = 0;
	while (input[i])
	{
		if (ft_strchr(input[i], '$') && ft_strchr(input[i], '"'))
		{
			expanded = expand_vars(input[i], envp_dict, true, false);
			free(input[i]);
			input[i] = expanded;
		}
		i++;
	}
}
