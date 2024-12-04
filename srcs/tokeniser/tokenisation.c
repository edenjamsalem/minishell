/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:26:42 by mganchev          #+#    #+#             */
/*   Updated: 2024/12/04 18:38:58 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// find the next token in input matching ref
int	find_next_token(t_token *tokens, enum e_token ref)
{
	int	i;
	
	i = 0;
	while (tokens[i])
	{
		if (tokens[i] == ref)
			return (i);
		i++;
	}
	return (-1);
}

t_token	get_prev_token(t_token *tokens, int index)
{
	return (tokens[index - 1]);
}

// initial tokenisation for redirections, control ops and quotes only
// had to put control ops here as well so i can keep track of them before
// i have to set cmd->condition for cmds in input
t_token	*primary_tokenisation(t_arrlst *words, t_token **tokens)
{
	int	i;
	
	i = 0;
	while (words->content[i])
	{
		if (is_redirect(words->content[i]))
			(*tokens)[i] = REDIRECT;
		else if (is_control(words->content[i]))
			(*tokens)[i] = CTRL_OP;
		else if (is_pipe(words->content[i]))
			(*tokens)[i] = PIPE;
		else
			(*tokens)[i] = TEXT;
		i++;
	}
	return (*tokens);
}

// consequent tokenisation for all other tokens + creation of cmds list
t_token	*secondary_tokenisation(t_arrlst *words, t_token **tokens)
{
	int	i;

	i = 0;
	while (words->content[i])
	{
		if (is_command(i, *tokens))
			(*tokens)[i] = CMD_;
		else if (is_file(i, *tokens))
			(*tokens)[i] = DIRECT;
		i++;
	}
	return (*tokens);
}

t_token *tokenise(t_arrlst *words)
{
	t_token	*tokens;

	tokens = malloc(sizeof(t_token) * words->count);
	if (!tokens)
		return (NULL);
	tokens = primary_tokenisation(words, &tokens);
	tokens = secondary_tokenisation(words, &tokens);
	return (tokens);
}

/*
const char *token_to_string(t_token token)
{
    switch (token)
    {
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

int main()
{
    t_arrlst words;
    t_token *tokens;
    int i;

    char *sample_input[] = {"echo", "hello", ">", "file.txt", "|", "grep", "hello", NULL};
    words.content = (void **)sample_input;
    words.count = 7;

    tokens = tokenise(&words);
    if (!tokens)
    {
        fprintf(stderr, "Tokenisation failed\n");
        return 1;
    }
    for (i = 0; i < words.count; i++)
    {
        printf("Token %d: %s\n", i, token_to_string(tokens[i]));
    }
    free(tokens);
    return 0;
}
*/