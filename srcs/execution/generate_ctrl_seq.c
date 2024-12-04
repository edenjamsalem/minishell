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

static void	assign_ctrl_op(t_ctrl_seq *seq, char *operator)
{
	// TESTED
	if (MATCH(operator, "&&"))
		seq->ctrl_op = AND;
	else if (ft_match(operator, "||"))
		seq->ctrl_op = OR;
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

static void	append_cmds(t_arrlst *cmds, void **input, t_token *tokens)
{
	char	**cmd_argv;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (input[i])
	{
		cmd_argv = malloc(sizeof(char *) * get_cmd_len(input, tokens) + 1);
		if (!cmd_argv)
			return ;
		while (input[i] && tokens[i] != CTRL_OP && tokens[i] != PIPE)
		{
			if (tokens[i] == CMD || tokens[i] == TEXT)
			{
				cmd_argv[j] = ft_strdup(input[i]);
			//	ft_printf("cmd_argv = %s\n", cmd_argv[j]);
				j++;
			}
			i++;
		}
		cmd_argv[j] = NULL;
		append_arrlst(cmds, cmd_argv);
		if (tokens[i] == CTRL_OP)
		{
			cmd_argv[j] = NULL;
			break ;
		}
		if (tokens[i] == PIPE)
			i++;
	}
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
	t_ctrl_seq	**ctrl_seq;
	int			i;
	int			j;
	int			count;

	count = get_seq_count(tokens, input->count);
	ctrl_seq = malloc(sizeof(t_ctrl_seq *) * count + 1);
	if (!ctrl_seq)
		return (NULL);
	i = 0;
	j = 0;
	while (input->content[i] && j < count)
	{
		ctrl_seq[j] = init_seq();
		handle_redirections(ctrl_seq[j], input->content + i, tokens + i);
		assign_ctrl_op(ctrl_seq[j], input->content[i]);
		append_cmds(ctrl_seq[j]->cmds, input->content + i, tokens + i);
		while (input->content[i] && tokens[i] != CTRL_OP)
			i++;
		j++;
	}
	ctrl_seq[j] = NULL;
//	allocate_pipes(ctrl_seq);
	return (ctrl_seq);
}

int main(int argc, char **argv, char **envp)
{
	char		*input = "head -n 5 >file1 | tail -n 2 && echo hello";
	t_dict		*envp_dict = init_envp_dict(envp);
	t_arrlst	*parsed_input;
	t_token 	*tokens; 
	t_ctrl_seq	**ctrl_seq;
	int			i;
	int			j;
	int			k;

	(void)argc;
	(void)argv;
	parsed_input = parse(input, envp_dict);
	tokens = tokenise(parsed_input);
	quote_removal(parsed_input);
	ctrl_seq = generate_ctrl_seq(parsed_input, tokens);
	i = 0;
	while (ctrl_seq[i])
	{
		ft_printf("COMMANDS: ");
		j = 0;
		while (ctrl_seq[i]->cmds->content[j])
		{
			k = 0;
			while (((char **)(ctrl_seq[i]->cmds->content[j]))[k])
				ft_printf("%s ", ((char **)(ctrl_seq[i]->cmds->content[j]))[k++]);
			ft_printf(",");
			j++;
		}
		ft_printf("\nCTRL OP: %d\n", ctrl_seq[i]->ctrl_op);
		ft_printf("INFILE: %d\n", ctrl_seq[i]->infile);
		ft_printf("OUTFILE: %d\n", ctrl_seq[i]->outfile);
		ft_printf("EXIT STATUS: %d\n\n", ctrl_seq[i]->prev_exit_status);
		i++;
	}
	dict_clear(&envp_dict);
	free_arrlst(parsed_input, free);
	free(parsed_input);
	//execute(ctrl_seq);
}