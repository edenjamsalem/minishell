/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:49:41 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/18 16:08:02 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//This function checks if the first occurrence of a chr in set is not in quotes
bool	contains(char *word, char *set)
{
	char		*first_quote;
	char		*second_quote;

	set = ft_strchrset(word, set);
	if (!set)
		return (false);
	first_quote = ft_strchrset(word, QUOTES);
	if (!first_quote)
		return (true);
	second_quote = ft_strchrset(first_quote + 1, QUOTES);
	if(!second_quote)
		return (true);
	if (set > first_quote && set < second_quote)
		return (false);
	return (true);
}

