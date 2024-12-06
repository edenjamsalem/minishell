/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 15:55:29 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/28 16:326:03y eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_ctrl_seq	*init_seq()
{
	// TESTED
	t_ctrl_seq *seq;

	seq = malloc(sizeof(t_ctrl_seq));
	if (!seq)
		return (NULL);
	seq->cmds = init_arrlst(2);
	if (!seq->cmds)
		return (NULL); // handle freeing properly
	seq->pipe_fd = NULL;
	seq->ctrl_op = NONE;
	seq->infile = STDIN_FILENO;
	seq->outfile = STDOUT_FILENO;
	seq->prev_exit_status = EXIT_SUCCESS;
	return (seq);
}

static int	assign_ctrl_op(t_ctrl_seq *seq, char *operator)
{
	// TESTED
	if (ft_match(operator, "&&"))
	{
		seq->ctrl_op = AND;
		return (1);
	}
	else if (ft_match(operator, "||"))
	{
		seq->ctrl_op = OR;
		return (1);
	}
	return (0);
}

static int get_cmd_len(void **input, t_token *tokens)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (input[i] && tokens[i] != PIPE && tokens[i] != CTRL_OP)
	{
		if (tokens[i] != REDIRECT && tokens[i] != FILE_)
			len++;
		i++;
	}
	return (len);
}

static int	append_cmds(t_arrlst *cmds, void **input, t_token *tokens)
{
	char	**cmd_argv;
	int		i;
	int		j;

	i = 0;
	while (input[i] && tokens[i] != CTRL_OP)
	{
		j = 0;
		cmd_argv = malloc(sizeof(char *) * (get_cmd_len(input, tokens) + 1));
		if (!cmd_argv)
			return (-1); // handle malloc error
		while (input[i] && tokens[i] != CTRL_OP && tokens[i] != PIPE)
		{
			if (tokens[i] == CMD || tokens[i] == TEXT)
				cmd_argv[j++] = ft_strdup(input[i]);
			i++;
		}
		cmd_argv[j] = NULL;
		append_arrlst(cmds, (void *)cmd_argv);
		if (tokens[i] == PIPE)
			i++;
	}
	return (i);
}

static int	get_seq_count(t_token *tokens, int size)
{
	// TESTED
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < size)
	{
		if (tokens[i] == CTRL_OP)
			count++;
		i++;
	}
	return (count + 1);
}

t_ctrl_seq	**generate_ctrl_seq(t_arrlst *input, t_token *tokens)
{
	// TESTED
	t_ctrl_seq	**ctrl_seq;
	int			i;
	int			j;
	int			count;

	count = get_seq_count(tokens, input->count);
	ctrl_seq = malloc(sizeof(t_ctrl_seq *) * (count + 1));
	if (!ctrl_seq)
		return (NULL);
	i = 0;
	j = 0;
	while (input->content[i])
	{
//		write(1, "1\n", 2);
		ctrl_seq[j] = init_seq();
		handle_redirections(ctrl_seq[j], input->content + i, tokens + i);
		i += assign_ctrl_op(ctrl_seq[j], input->content[i]);
		i += append_cmds(ctrl_seq[j]->cmds, input->content + i, tokens + i);
		allocate_pipe_fd(ctrl_seq[j], ctrl_seq[j]->cmds->count - 1);
		j++;
	}
	ctrl_seq[j] = NULL;
	return (ctrl_seq);
}

/*
int main(int argc, char **argv, char **envp)
{
	char		*input = " head -n 5 <file2>file1 | tail -n 2 || echo >file2 hello | echo hello || echo hello | echo hello";
	t_dict		*envp_dict = init_envp_dict(envp);
	t_arrlst	*words;
	t_token 	*tokens; 
	t_ctrl_seq	**ctrl_seq;
	int			i;
	int			j;
	int			k;

	(void)argc;
	(void)argv;
	words = parse(input, envp_dict);
	tokens = tokenise(words);
	quote_removal(words);

	i = 0;
	while (i < words->count)
	{
		ft_printf("%s:%d\n", words->content[i], tokens[i]);
		i++;
	}

	ctrl_seq = generate_ctrl_seq(words, tokens);
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
			ft_printf(",");
			j++;
		}
		ft_printf("\nCTRL OP: %d\n", ctrl_seq[i]->ctrl_op);
		ft_printf("INFILE: %d\n", ctrl_seq[i]->infile);
		ft_printf("OUTFILE: %d\n", ctrl_seq[i]->outfile);
		ft_printf("PIPE COUNT = %d\n", ft_2darr_len((void **)(ctrl_seq[i]->pipe_fd)));
		ft_printf("EXIT STATUS: %d\n\n", ctrl_seq[i]->prev_exit_status);
		i++;
	}
	dict_clear(&envp_dict);
	free_arrlst(words, free);
	free(words);
	//execute(ctrl_seq);
}
*/