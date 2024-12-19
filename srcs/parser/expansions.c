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

char	*expand_vars(char *input, t_dict *envp, bool inc_double, bool inc_single)
{
	char	expanded[2048];
	char	*ptr;

	if (single_quotes_inside_double(input))
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