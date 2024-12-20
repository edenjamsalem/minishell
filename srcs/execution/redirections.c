/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:31:16 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 15:21:06 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if words succeeding redirection symbols are more than 1 word long post-expansion
// -> we report an error

void	setup_pipes(t_cmd_seq *cmd_seq)
{
	int	i;

	cmd_seq->pipe_fd = NULL;
	if (cmd_seq->pipe_count == 0)
		return ;
	cmd_seq->pipe_fd = malloc(sizeof(int *) * (cmd_seq->pipe_count + 1));
	if (!cmd_seq->pipe_fd)
		return ;
	i = 0;
	while (i < cmd_seq->pipe_count)
	{
		cmd_seq->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!cmd_seq->pipe_fd[i])
		{
			free_2darr((void *)cmd_seq->pipe_fd, i - 1);
			return ;
		}
		i++;
	}
	cmd_seq->pipe_fd[i] = NULL;
}

static bool	is_eof(char *input, char *eof)
{
	if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		if (ft_strlen(input) - 1 == ft_strlen(eof))
			return (true);
	}
	return (false);
}

static void	get_heredoc_input(char *eof, int *pipe_fd, t_dict *envp)
{
	int		bytes_read;
	char	input[4096];
	char	*expanded;
	static int	line_count;  // to count lines of here_doc for bash error message
	
	while (1)
	{
		write(1, "> ", 2);
		bytes_read = read(STDIN_FILENO, input, 4096);
		line_count++; 
		if (bytes_read == -1)
			exit(EXIT_FAILURE);
		if (bytes_read == 0)
			handle_ctrl_d(bytes_read, line_count, eof);
		input[bytes_read] = '\0';
		if (is_eof(input, eof))
			exit(EXIT_SUCCESS);
		expanded = expand_vars(input, envp, true, true);
		write(pipe_fd[1], expanded, ft_strlen(expanded));
		free(expanded);
	}
}

int	open_heredoc(char *eof, t_dict *envp)
{
	pid_t	pid;
	int		pipe_fd[2];
	
	signal(SIGINT, SIG_IGN);
	pid = pipe_fork(pipe_fd);
	if (!pid)
	{
		signal(SIGINT, handle_ctrl_c_child);
		close(pipe_fd[0]);
		get_heredoc_input(eof, pipe_fd, envp);
	}
	close(pipe_fd[1]);
	wait(0);
	setup_sig_handler(SIGINT);
	return (pipe_fd[0]);
}

void	assign_redirections(t_cmd_seq *cmd_seq, t_dict *envp)
{
	char *operator;
	char *file;
	int	i;

	cmd_seq->infile = STDIN_FILENO;
	cmd_seq->outfile = STDOUT_FILENO;
	i = 0;
	while (cmd_seq->words->content[i])
	{
		if (cmd_seq->tokens[i] == REDIRECT && cmd_seq->tokens[i + 1] == FILE_)
		{
			operator = cmd_seq->words->content[i];
			file = cmd_seq->words->content[i + 1];
			if (ft_match(operator, ">"))
				cmd_seq->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0643);
			else if (ft_match(operator, ">>"))
				cmd_seq->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0643);
			else if (ft_match(operator, "<"))
				cmd_seq->infile = open(file, O_RDONLY);
			else if (ft_match(operator, "<<"))
				cmd_seq->infile = open_heredoc(file, envp);
		}
		i++;
	}
}
