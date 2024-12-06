/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:24:14 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/06 15:33:43 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks for every token that isn't supposed to repeat
bool    is_repeat(t_token *tokens, int count, int *index)
{
    // causing memory leaks as trying to check prev token for first token
    int i;

    i = 0;
    while (i < count)
    {
        if (tokens[i] == CTRL_OP || tokens[i] == REDIRECT || tokens[i] == PIPE)
        {
            if (get_prev_token(tokens, i) == CTRL_OP)
            {
                *index = i;
                return (true);
            }
            else if (get_prev_token(tokens, i) == REDIRECT)
            {
                *index = i;
                return (true);
            }
            else if (get_prev_token(tokens, i) == PIPE)
            {
                *index = i;
                return (true);
            }
        }
        i++;
    }
    return (false);
}

// checks syntax of file names following REDIRECT
bool    is_file_name(t_arrlst *words, t_token *tokens, int *index)
{
    int i;

    i = 0;
    while (i < words->count)
    {
        if (tokens[i] == REDIRECT)
        {
            if (ft_strchrset(words->content[i + 1], IFS))
            {
                *index = i + 1;
                return (false);
            }
        }
        i++;
    }
    return (true);
}

// custom perror function
void    ft_perror(t_error type, char *error_msg)
{
    if (type == SYNTAX)
        ft_fprintf(2, "syntax error near unexpected token `%s'", error_msg);
    else if (type == CMD_)
        ft_fprintf(2, "`%s': command not found", error_msg);
    else if (type == DIRECT)
        ft_fprintf(2, "`%s': No such file or directory", error_msg);
    exit(EXIT_FAILURE); 
}

// prints error messages in case of syntax error
void    grammar_check(t_arrlst *words, t_token *tokens)
{
    int index;
    
    index = -1;
    if (is_repeat(tokens, words->count, &index))
    {
        if (tokens[index] == REDIRECT && get_prev_token(tokens, index) != REDIRECT)
            return (ft_perror(SYNTAX, "newline"));
        return (ft_perror(SYNTAX, (char *)words->content[index]));
    }
    else if (!is_file_name(words, tokens, &index))
        return (ft_perror(DIRECT, (char *)words->content[index]));
}
