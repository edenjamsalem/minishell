/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 10:07:28 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 22:46:32 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_echo(char *text, bool n_flag)
{	
	if (text)
	{
		text += 5;
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
		ft_printf("%% \n");
	else if (!n_flag || !text)
		ft_printf("\n");
}
