/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:21:33 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/18 19:24:28 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    print_arrlst(t_arrlst *list)
{
    int i;

    i = 0;
    if (!list->content[0])
    {
        printf("%d\n", list->capacity);
        return ;
    }
    while (list->content[i])
    {
        printf("%s ", (char *)list->content[i]);
        i++;
    }
    printf("\n");
}

char *token_to_string(t_token token)
{    
    switch (token)
    {
    case END:
        return "END";
    case REDIRECT:
        return "REDIRECT";
    case PIPE:
        return "PIPE";
    case TEXT:
        return "TEXT";
    case CMD:
        return "CMD";
    case FILE_:
        return "FILE_";
    default:
        return "UNKNOWN";
    }
}
    
void    print_tokens(t_arrlst *words, t_token *tokens)
{
    int i;
    
    for (i = 0; i <= words->count; i++)
        printf("Token %d: %s\n", i, token_to_string(tokens[i]));
    printf("\n");
}
