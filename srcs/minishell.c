/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:06:19 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 12:22:47by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// // initialise
// // set up signal handlers
// // parse input
// tokenise parsed input > skip quotes when checking for PIPE, CTRL OP and REDIRECT
// // quote removal
// // set up control seq
// // execute
// free
volatile sig_atomic_t	g_flag = 0; // signal receiving flag

void print_arrlst(t_arrlst *list);
void print_tokens(t_arrlst *words, t_token *tokens);
void print_ctrl_seq(t_ctrl_seq **ctrl_seq);

// set up envp dictionary
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

// read input, add history and handling signals
char	*read_input(void)
{
	char *input;
	char prompt[100];

	getcwd(prompt, sizeof(prompt));
	ft_strlcat(prompt, " > ", 100);
	input = readline(prompt);
	if (!input) // handling EOF / ctrl + D
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (*input)
		add_history(input);
	else
	{
		free(input); // handles ENTER key press
		return (NULL);
	}
	return (input);
}

int	input_unfinished(t_arrlst *input, t_token *tokens, t_dict *envp)
{
	int			bytes_read;
	char		*buf;
	t_arrlst	*rest_of_input;
	int			i;
	
	if (tokens[input->count - 1] == CTRL_OP || tokens[input->count - 1] == PIPE)
	{
		buf = malloc(4096);
		write(1, "> ", 2);
		bytes_read = read(STDIN_FILENO, buf, 4096);
		buf[bytes_read] = '\0';
		rest_of_input = parse(buf, envp);
		i = 0;
		while (i < rest_of_input->count)
		{
			append_arrlst(input, rest_of_input->content[i]);
			i++;
		}
		// check why double free for buf if I free here
		return (1);
	}
	return (0);
}

// process input, generate ctrl seq and execute
void	process(char *input, t_dict *envp)
{
	t_arrlst	*words;
	t_token		*tokens;
	t_ctrl_seq	**ctrl_seq;
	
	words = NULL;
	words = parse(input, envp);
	if (!words)
	{
		free_2darr(words->content, ft_2darr_len(words->content)), free(words);
		return ;
	}
	tokens = tokenise(words);
	if (!tokens)
		return ; // need to free mem here
	if (input_unfinished(words, tokens, envp))
	{
		free(tokens);
		tokens = tokenise(words);
	}
	quote_removal(words);
	ctrl_seq = generate_ctrl_seq(words, tokens, envp);
	execute(ctrl_seq, envp);
	free_2darr(words->content, ft_2darr_len(words->content));
	free(words);
}

// clean up function
void	cleanup(t_dict *envp_dict)
{
	rl_clear_history();
	dict_clear(&envp_dict);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_dict	*envp_dict;

	(void)argc;
	(void)argv;
	envp_dict = init_envp_dict(envp);
	setup_sig_handlers(); // initialise signal handlers first;
	while (1)
	{
		if (g_flag) // means a message is being received
		{	
			g_flag = 0; // reset flag
			//input = readline("minishell > "); // reset prompt | MAYBE DONT NEED ?
			continue ;
		}
		input = read_input();
		if (!input)
			continue ;
		process(input, envp_dict);
	}
	cleanup(envp_dict);
}
