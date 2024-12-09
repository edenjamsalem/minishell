/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 23:21:33 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/06 21:25:46 by mganchev         ###   ########.fr       */
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
    case CTRL_OP:
        return "CTRL_OP";
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

void    print_ctrl_seq(t_ctrl_seq **ctrl_seq)
{
    int i, j, k;
    
    i = 0;
	while (ctrl_seq[i])
	{
		char ***cmds = (char ***)(ctrl_seq[i]->cmds->content);
		ft_printf("COMMANDS: ");
		j = 0;
		while (cmds[j])
		{
			k = 0;
			while (cmds[j][k])
				ft_printf("%s ", cmds[j][k++]);
			j++;
		}
		ft_printf("\nCTRL OP: %d\n", ctrl_seq[i]->ctrl_op);
		ft_printf("INFILE: %d\n", ctrl_seq[i]->infile);
		ft_printf("OUTFILE: %d\n", ctrl_seq[i]->outfile);
		ft_printf("EXIT STATUS: %d\n\n", ctrl_seq[i]->prev_exit_status);
		i++;
	}
}

