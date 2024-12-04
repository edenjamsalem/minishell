/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:24:14 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/04 18:38:54 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// // CTRL OP can't be followed by another CTRL OP 
// // PIPE can't be followed by another PIPE
// // REDIRECT can't be followed by another REDIRECT
// // FILE_ can't have space 
// // here_doc terminator must not be surrounded by spaces + must match

// checks for every token that isn't supposed to repeat
bool    is_repeat(t_token *tokens, int count, int *index)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (tokens[i] == CTRL_OP && get_prev_token(tokens, i) == CTRL_OP)
        {
            index = i;
            return (true);
        }
        else if (tokens[i] == REDIRECT && get_prev_token(tokens, i) == REDIRECT)
        {
            index = i;
            return (true);
        }
        else if (tokens[i] == PIPE && get_prev_token(tokens, i) == PIPE)
        {
            index = i;
            return (true);
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
                index = i + 1;
                return (false);
            }
        }
        i++;
    }
    return (true);
}

void    ft_perror(t_error type, char *error_msg)
{
    if (type == SYNTAX)
        ft_fprintf(2, "syntax error near unexpected token %s", error_msg);
    else if (type == CMD_)
        ft_fprintf(2, "%s: command not found", error_msg);
    else if (type == DIRECT)
        ft_fprintf(2, "%s: No such file or directory", error_msg);
}

// prints error messages in case of syntax error
void    grammar_check(t_arrlst *words, t_token *tokens)
{
    int index;
    
    index = -1;
    if (is_repeat(tokens, words->count, &index))
        return (ft_perror(SYNTAX, words->content[index])); // function that builds a perror message with a specific string
    else if (!is_file_name(words, tokens, &index))
        return (ft_perror(DIRECT, words->content[index]));
}
