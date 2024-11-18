/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 11:56:09 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/18 15:39:51 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_quoted_text(char **input, char **expanded)
{
	char	*closing_quote;

	if (!(*input) || !(*expanded))
		return ;
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

	if (!(*input) || !(*expanded) || !(envp_dict))
		return ;	
	(*input)++;	
	key = ft_strcut(*input, skip_alnum(input));
	value = get_dict_value(key, envp_dict);
	if (value)
	{
		ft_strlcpy(*expanded, value, ft_strlen(value) + 1);	
		skip_word(expanded);
	}
	skip_alnum(input);
	free(key);
}
