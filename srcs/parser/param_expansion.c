/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:45:18 by mganchev          #+#    #+#             */
/*   Updated: 2024/11/19 17:10:34 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../../minishell.h"
#include <stdio.h>

// extract param value from input
char	*extract_param(char **input, char **output, t_dict *envp_dict)
{
	char	*param;
	char	*temp;
	char	*end;

	(*input)++;
	end = *input;
	param = ft_strcut(*input, skip(&end, ft_isalnum));
	temp = get_dict_value(param, envp_dict);
	if (temp)
	{
		ft_strlcpy(*output, temp, ft_strlen(temp) + 1);
		*output += ft_strlen(temp);
	}
	else
	{
		*(*output)++ = '$';
		ft_strlcpy(*output, param, ft_strlen(param) + 1);
		*output += ft_strlen(param);
	}
	free(param);
	*input = end;
	return (*output);
}

// expand params
char	*expand_params(char *input, t_dict *envp_dict)
{
	char	*output;
	char	*start;

	output = malloc(ft_strlen(input) * 2);
	if (!output)
		return (NULL);
	start = output;
	while (*input)
	{
		if (*input == '"' || *input == '\'')
			output += skip_quotes(&input);
		if (*input == '$' && *(input - 1) != '\\')
			extract_param(&input, &output, envp_dict);
		else
			*output++ = *input++;
	}
	*output = '\0';
	return (start);
}
/*
int	main(int argc, char **argv, char **envp)
{
	t_dict	*envp_dict;
	char	input[] = "Hello $USER, your home directory is $HOME and your shell is $SHELL.";
	char	*expanded;

	// Initialize the environment dictionary
	envp_dict = init_envp_dict(envp);
	// Test input string
	// Expand parameters and print the result
	expanded = expand_params(input, envp_dict);
	printf("Expanded: %s\n", expanded);
	// Free the environment dictionary if necessary
	// free_envp_dict(envp_dict);
		// Uncomment if you have a function to free the dictionary
	free(expanded);
	return (0);
} */
