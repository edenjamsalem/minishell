/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:51 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/20 19:04:42 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int    ft_perror(t_error type, char *error_msg)
{
    if (type == SYNTAX)
    {
        ft_fprintf(2, "syntax error near unexpected token '%s'\n", error_msg);
        return (0);
    }
    else if (type == CMD_)
    {
        ft_fprintf(2, "'%s': command not found\n", error_msg);
        return (0);
    }
    else if (type == DIRECT)
    {
        ft_fprintf(2, "'%s': No such file or directory\n", error_msg); 
        return (0);
    }
    return (1);
}

