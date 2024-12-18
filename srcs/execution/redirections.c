/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:31:16 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/18 23:46:30 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if words succeeding redirection symbols are more than 1 word long post-expansion
// -> we report an error

bool	is_eof(char *input, char *eof)
{
	if (ft_strncmp(input, eof, ft_strlen(eof)) == 0)
	{
		if (ft_strlen(input) - 1 == ft_strlen(eof))
			return (true);
	}
	return (false);
}

void	setup_pipes(t_cmd_seq *command)
{
	int	i;
	int	pipe_count;

	pipe_count = command->pipe_count;
	if (pipe_count < 1)
		return ;
	command->pipe_fd = malloc(sizeof(int *) * (pipe_count + 1));
	if (!command->pipe_fd)
		return ;
	i = 0;
	while (i < pipe_count)
	{
		command->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!command->pipe_fd[i])
		{
			free_2darr((void *)command->pipe_fd, i - 1);
			return ;
		}
		i++;
	}
	command->pipe_fd[pipe_count] = NULL;
}

int	get_heredoc_input(char *eof, t_dict *envp)
{
	pid_t	pid;
	char	input[4096];
	int		pipe_fd[2];
	int		bytes_read;
	char	*expanded;
	static int	line_count;  // to count lines of here_doc for bash error message
	
	signal(SIGINT, SIG_IGN);
	pid = pipe_fork(pipe_fd);
	if (!pid)
	{
		signal(SIGINT, handle_ctrl_c_child);
		close(pipe_fd[0]);
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
	else
	{
		close(pipe_fd[1]);
		wait(0);
		setup_sig_handler(SIGINT);
	}
	return (pipe_fd[0]);
}

void	assign_redirections(t_cmd_seq *command, t_dict *envp)
{
	char *operator;
	char *file;
	int	i;

	command->infile = STDIN_FILENO;
	command->outfile = STDOUT_FILENO;
	i = 0;
	while (command->words->content[i])
	{
		if (command->tokens[i] == REDIRECT && command->tokens[i + 1] == FILE_)
		{
			operator = command->words->content[i];
			file = command->words->content[i + 1];
			if (ft_match(operator, ">"))
				command->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0643);
			else if (ft_match(operator, ">>"))
				command->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0643);
			else if (ft_match(operator, "<"))
				command->infile = open(file, O_RDONLY);
			else if (ft_match(operator, "<<"))
				command->infile = get_heredoc_input(file, envp);
		}
		i++;
	}
}
