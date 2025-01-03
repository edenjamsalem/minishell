/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 15:52:45 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/03 13:39:19 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	int			bytes_read;
	char		input[4096];
	char		*expanded;
	static int	line_count;

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
		{
			close(pipe_fd[1]);
			exit(EXIT_SUCCESS);
		}
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
	if (CHILD_PROCESS)
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

static int	open_file(char *file, char *op, t_cmd_seq *cmd_seq, t_dict *envp)
{
	int	fd;

	fd = -1;
	if (ft_match(op, ">"))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0643);
		cmd_seq->outfile = fd;
	}
	else if (ft_match(op, ">>"))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0643);
		cmd_seq->outfile = fd;
	}
	else if (ft_match(op, "<"))
	{
		fd = open(file, O_RDONLY);
		cmd_seq->infile = fd;
	}
	else if (ft_match(op, "<<"))
	{
		fd = open_heredoc(file, envp);
		cmd_seq->infile = fd;
	}
	return (fd);
}

void	assign_redirections(t_cmd_seq *cmd_seq, t_dict *envp)
{
	char	*operator;
	char	*file;
	int		open_fds[100];
	int		i;
	int		j;

	cmd_seq->infile = STDIN_FILENO;
	cmd_seq->outfile = STDOUT_FILENO;
	i = 0;
	j = 0;
	while (cmd_seq->words->content[i])
	{
		if (cmd_seq->tokens[i] == REDIRECT && cmd_seq->tokens[i + 1] == FILE_)
		{
			operator = cmd_seq->words->content[i];
			file = cmd_seq->words->content[i + 1];
			open_fds[j] = open_file(file, operator, cmd_seq, envp);
			j++;
		}
		i++;
	}
	cmd_seq->open_fds = int_arrdup(open_fds, j);
	cmd_seq->open_fd_count = j;
}
