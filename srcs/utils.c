/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 17:05:51 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/06 20:46:05 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// replacement for MATCH macro
bool ft_match(char *s1, char *s2)
{
    return (ft_strncmp(s1, s2, ft_strlen(s1) + 1) == 0);
}

// returns previous token in array, mainly for code readability
t_token	get_prev_token(t_token *tokens, int index)
{
	if (index == 0)
        return (END);
    return (tokens[index - 1]);
}

void    ft_perror(t_error type, char *error_msg)
{
    if (type == SYNTAX)
        ft_fprintf(2, "syntax error near unexpected token `%s'", error_msg);
    else if (type == CMD_)
        ft_fprintf(2, "`%s': command not found", error_msg);
    else if (type == DIRECT)
        ft_fprintf(2, "`%s': No such file or directory", error_msg); 
    return ;
}
