/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:28 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/03 12:26:56 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char *text, bool n_flag)
{
	if (!text)
		return (0);
	printf("%s", text);
	if (!n_flag)
		printf("\n");
	return (1);
}
