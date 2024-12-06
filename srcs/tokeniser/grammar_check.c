/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar_check.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 21:24:14 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/06 17:22:04 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// checks for every token that isn't supposed to repeat
bool    is_repeat(t_token *tokens, int count, int *index)
{
    int i;

    i = 0;
    while (i < count)
    {
        if (tokens[i] == CTRL_OP || tokens[i] == PIPE)
        {
            if (get_prev_token(tokens, i) == CTRL_OP)
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

// check if input is starting on PIPE and CTRL OP
bool    is_start(t_token *tokens, int *index)
{
    if (tokens[0] == CTRL_OP || tokens[0] == PIPE)
    {
        index = 0;
        return (false);
    }
    return (true);
}

// check if REDIRECT is at the end of the line without any FILE_ following
bool    is_redirect_correct(t_arrlst *words, t_token *tokens, int *index)
{
    int i;

    i = 0;
    while (i < words->count)
    {
        if (tokens[i] == REDIRECT && !(tokens[i + 1]))
            return (false);
    }
    return (true);
}

// prints error messages in case of syntax error
void    grammar_check(t_arrlst *words, t_token *tokens)
{
    int index;
    
    index = -1;
    if (is_start(tokens, &index))
        return (ft_perror(SYNTAX, words->content[index]));
    else if (is_repeat(tokens, words->count, &index))
        return (ft_perror(SYNTAX, (char *)words->content[index]));
    else if (!is_redirect_correct(words, tokens, &index))
        return (ft_perror(SYNTAX, "newline"));
    else if (!is_file_name(words, tokens, &index))
        return (ft_perror(DIRECT, (char *)words->content[index]));
}
