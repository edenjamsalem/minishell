/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:43:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/15 14:55:24by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// This function calculates the diff in len between a $var and its expansion
static int	calc_diff(char *key, t_dict *envp_dict)
{
	char	*value;

	value = get_dict_value(key, envp_dict);
	return (ft_strlen(value) - (ft_strlen(key) + 1));
}

// This function calculates the expanded len of the input
static int	get_len(char *input, t_dict *envp_dict, bool ignore_quoted_vars)
{
	int		input_len;
	int		diff;
	char	*var;
	
	diff = 0;
	input_len = ft_strlen(input);
	while (*input)
	{
		if (*input == '\'')
			skip_quotes(&input);// handles unclosed quotes
		else if (*input == '\"' && ignore_quoted_vars)
			skip_quotes(&input);
		else if (*input == '$')
		{
			input++;
			var = ft_strcut(input, skip_alnum(&input));
			diff += calc_diff(var, envp_dict);
			free(var);
		}
		else
			input++;
	}
	return (input_len + diff);
}

char	*expand_vars(char *input, t_dict *envp_dict, bool ignore_quoted_vars)
{
	char	*expanded;
	char	*ptr;

	expanded = malloc((get_len(input, envp_dict, ignore_quoted_vars) + 1));
	if (!expanded)
		return (NULL);
	ptr = expanded;
	while (*input)
	{
		if (*input == '\'')
			copy_quoted_text(&input, &expanded);
		else if (*input == '\"' && ignore_quoted_vars)
			copy_quoted_text(&input, &expanded);
		else if (*input == '$')
			copy_expanded_var(&input, &expanded, envp_dict);
		else
			*expanded++ = *input++;
	}
	*expanded = '\0';
	return (ptr);
}

void	expand_vars_inside_quotes(t_list_2 *input, t_dict *envp_dict)
{
	t_word	*word;
	char	*expanded;

	while (input)
	{
		word = (t_word *)(input->content);
		if (ft_strchr(word->text, '$') && ft_strchr(word->text, '\"'))
		{
			expanded = expand_vars(word->text, envp_dict, INC_QUOTED_VARS);
			free(word->text);
			word->text = expanded;
		}
		input = input->next;
	}
}


/*
int main(int argc, char **argv, char **envp)
{
	t_dict *envp_dict = init_envp_dict(envp);	

	printf("%d\n", get_len("\'$LANGUAGE\' $PATH", envp_dict));
}
*/