/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/04 19:52:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

volatile sig_atomic_t	g_flag = 0; // signal receiving flag

t_dict	*init_envp_dict(char **envp)
{
	int			i;
	t_dict		*node;
	t_dict		*envp_dict;

	i = 0;
	envp_dict = NULL;
	while (envp[i])
	{
		node = str_to_dict(envp[i]);
		dict_addback(&envp_dict, node);
		i++;
	}
	return (envp_dict);
}
/*
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_dict		*envp_dict;
	t_arrlst	*parsed_input;
	e_token		*tokens;
	t_ctrl_seq	**ctrl_seq;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	setup_sig_handlers(); // initialise signal handlers first;
	while (1)
	{
		if (g_flag) // means a message is being received
		{	
			g_flag = 0; // reset flag
			input = readline("minishell > "); // reset prompt
			continue ;
		}
		input = readline("minishell > ");
		if (!input) // handling EOF / ctrl + D
		{
			ft_printf("exit\n");
			break;
		}
		if (*input)
			add_history(input);
		else
		{
			free(input); // handles ENTER key press
			continue ;
		}
		parsed_input = parse(input, envp_dict);
		tokens = tokenise(parsed_input);
		ctrl_seq = generate_ctrl_seq(input->content, tokens);
		execute(ctrl_seq);
		
		while (parsed)
    	{
        	word = (t_word *)parsed->content;
        	printf("Word: %s, Token Type: %s\n", word->text, token_type_to_string(word->token));
        	parsed = parsed->next;
    	}
		free_2darr((void *)args, ft_2darr_len((void *)args));
		free(input);
	}
	rl_clear_history();
	dict_clear(&envp_dict);
}
*/