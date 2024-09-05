/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:28 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/05 13:27:41 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char *text, bool n_flag)
{
	if (!text)
	{
		printf("\n");
		return ;
	}
	printf("%s", text);
	if (!n_flag)
		printf("\n");
}
