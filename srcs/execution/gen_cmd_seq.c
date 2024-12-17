/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctrl_seq.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 14:52:24 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/13 14:53:05 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	assign_pipe_count(t_cmd_seq *command)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (command->tokens[i] != END)
	{
		if (command->tokens[i] == PIPE)
			count++;
		i++;
	}
	command->pipe_count = count;
}


static int get_cmd_len(t_token *tokens)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (tokens[i] != END && tokens[i] != PIPE)
	{
		if (tokens[i] == CMD || tokens[i] == TEXT)
			len++;
		i++;
	}
	return (len);
}

void	assign_cmds(t_cmd_seq *command)
{
	int		i;
	int		j;
	int		k;

	command->cmds = malloc(sizeof(char **) * (command->pipe_count + 2));
	if (!command->cmds)
		return ;
	i = 0;
	k = 0;
	while (i < command->pipe_count + 1)
	{
		command->cmds[i] = malloc(sizeof(char *) * (get_cmd_len(command->tokens) + 1));
		if (!command->cmds[i])
			return ;
		j = 0;
		while (command->tokens[k] != END && command->tokens[k] != PIPE)
		{
			if (command->tokens[k] == CMD || command->tokens[k] == TEXT)
				command->cmds[i][j++] = ft_strdup(command->words->content[k]);
			k++;
		}
		command->cmds[i][j] = NULL;
		if (command->tokens[k] == PIPE)
			k++;
		i++;
	}
	command->cmds[i] = NULL;
}

t_cmd_seq	*gen_cmd_seq(char *input, t_dict *envp)
{
	t_cmd_seq *command;

	command = malloc(sizeof(t_cmd_seq));
	if (!command)
		return (NULL);
	parse(input, command, envp);
	assign_redirections(command, envp);
	assign_pipe_count(command);
	setup_pipes(command);
	assign_cmds(command);
	return (command);
}