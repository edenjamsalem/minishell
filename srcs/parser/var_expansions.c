/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:43:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 18:21:54 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// This function calculates the diff in len between a $var and its expansion
static int	calc_diff(char *key, t_dict *envp_dict)
{
	char *value;

	value = get_dict_value(key, envp_dict);
	if (value)
		return (ft_strlen(value) - (ft_strlen(key) + 1)); // +1 for $ sign
	return (-(ft_strlen(key) + 1));
}

// This function calculates the expanded len of the input
int	get_len(char *input, t_dict *envp_dict)
{
	int		input_len;
	int		diff;
	char	*var;
	
	diff = 0;
	input_len = ft_strlen(input);
	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			skip_quotes(&input);
		else if (*input == '$' && *(input - 1) != '\\')
		{
			input++;
			var = ft_strcut(input, skip_alnum(&input));
			diff += calc_diff(var, envp_dict);
			free(var);
		}
		input++;
	}
	return (input_len + diff);
}

void	copy_quoted_text(char **input, char **expanded)
{
	char	*closing_quote;

	closing_quote = (char *)ft_strchr(*input + 1, **input);
	if (closing_quote)
		ft_strlcpy(*expanded, *input, (closing_quote - *input + 2));
	else
		**expanded = **input;
	skip_quotes(input);
	skip_quotes(expanded);
}

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict)
{
	char	*key;
	char	*value;
	
	(*input)++;	
	key = ft_strcut(*input, skip_alnum(input));
	value = get_dict_value(key, envp_dict);
	ft_strlcpy(*expanded, value, ft_strlen(value) + 1);	
	skip_alnum(input);
	skip_word(expanded);
	free(key);
}

char	*expand_vars_outside_quotes(char *input, t_dict *envp_dict)
{
	char	*expanded;
	char	*ptr;
	
	expanded = malloc(sizeof(char) * (get_len(input, envp_dict) + 1));
	if (!expanded)
		return (NULL);
	ptr = expanded;
	while (*input)
	{
		if (chrsetcmp(*input, QUOTES))
			copy_quoted_text(&input, &expanded);
		else if (*input == '$' && *(input - 1) != '\\')
			copy_expanded_var(&input, &expanded, envp_dict);
		*expanded++ = *input++;
	}
	*expanded = '\0';
	return (ptr);
}

int main(int argc, char **argv, char **envp)
{
	t_dict *envp_dict = init_envp_dict(envp);	

	printf("%s\n", expand_vars_outside_quotes("$SHELL $ab  hello ", envp_dict));
}
