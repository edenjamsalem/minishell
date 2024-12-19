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

char	*expand_vars(char *input, t_dict *envp, bool inc_double, bool inc_single)
{
	char	expanded[2048];
	char	*ptr;

	if (ft_strchr(input, '"') < ft_strchr(input, '\''))
		inc_single = true;
	ptr = expanded;
	while (*input)
	{
		if (*input == '\'' && !inc_single)
			copy_quoted_text(&input, &ptr);
		else if (*input == '\"' && !inc_double)
			copy_quoted_text(&input, &ptr);
		else if (*input == '$' && *(++input) && !chrsetcmp(*input, IFS))
			copy_expanded_var(&input, &ptr, envp);
		else
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
/*
int main(int argc, char **argv, char **envp)
{
	t_dict *envp_dict = init_envp_dict(envp);	

	printf("%s\n", expand_vars(" This is my \"$PATH\" what>>\'isyours?", envp_dict, true));
}
*/