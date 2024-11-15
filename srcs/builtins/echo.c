/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:28 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/15 00:31:56 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char *text, bool n_flag)
{	
	if (text)
	{
		text += 5; // hardcoded skipping echo + -n for now, it should be tokenised before execution
		if (text[0] == '-' && text[1] == 'n')
		{
			text += 3;
			n_flag = true;
		}
		while (*text != '\0')
		{
			write(STDOUT_FILENO, text, 1);
			text++;
		}
	}
	if (n_flag)
		ft_printf("%% \n"); // % is there just to check if it's executing correctly
	else if (!n_flag || !text)
		ft_printf("\n");
}
