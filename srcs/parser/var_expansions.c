/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:43:34 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 12:05:03 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// changed dict struct to include list so I dont need 2 data types, 

// 				update all files accordingly !!




static void	swap_key_for_value(char **tmp_split, t_list_2 *envp_dict)
{
	char	*value;

	value = get_dict_value(tmp_split[1], envp_dict);
	free(tmp_split[1]);
	tmp_split[1] = value;
}

static char	**split_var_from_input(char *input, char *var)
{
	char	**tmp_split;

	tmp_split = malloc(sizeof(char *) * 4);
	tmp_split[0] = ft_strcut(input, var);
	tmp_split[1] = ft_strcut(var + 1, skip_word(&var));
	tmp_split[2] = ft_strdup(skip_word(&var));
	tmp_split[3] = 0;
	return (tmp_split);
}

char	*expand_vars_outside_quotes(char *input, t_list_2 *envp_dict)
{
	char	*current;
	char	**tmp_split;

	current = input;
	while (*current)
	{
		if (*current == '$' && *(current - 1) != '\\')
		{
			tmp_split = split_var_from_input(input, current);
			swap_key_for_value(tmp_split, envp_dict);
			current = ft_strunion(tmp_split);
		}
		current++;
	}
	
}

int main(void) {
/*	char	*str = "hello $my";
	char	*chr = str + 6;
	char	**tmp_split = split_var_from_input(str, chr);
	int		i = 0;

	while (tmp_split[i])
	{
		printf("%s\n", tmp_split[i]);
		i++;
	}*/

	
}