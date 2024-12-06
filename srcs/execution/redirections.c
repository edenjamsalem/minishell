/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:31:16 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 15:30:32 by eamsalem         ###   ########.fr       */
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

void	allocate_pipe_fd(t_ctrl_seq *seq, int size)
{
	int	i;

	if (size < 1)
		return ;
	seq->pipe_fd = malloc(sizeof(int *) * (size + 1));
	if (!seq->pipe_fd)
		return ;
	i = 0;
	while (i < size)
	{
		seq->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!seq->pipe_fd[i])
		{
			free_2darr((void *)seq->pipe_fd, i - 1);
			return ;
		}
		i++;
	}
	seq->pipe_fd[size] = NULL;
}

int	get_heredoc_input(char *eof)
{
	pid_t	pid;
	char	input[4096];
	int		pipe_fd[2];
	int		bytes_read;

	pid = pipe_fork(pipe_fd);
	if (!pid)
	{
		close(pipe_fd[0]);
		while (1)
		{
			write(1, "> ", 2);
			bytes_read = read(STDIN_FILENO, input, 4096);
			input[bytes_read] = '\0';
			if (is_eof(input, eof))
				exit(EXIT_SUCCESS);
			write(pipe_fd[1], input, bytes_read);
		}
	}
	close(pipe_fd[1]);
	wait(0);
	return (pipe_fd[0]);
}

void	redirect_fd(t_ctrl_seq *seq, char *operator, char *file)
{
	if (ft_match(operator, ">"))
		seq->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0643);
	else if (ft_match(operator, ">>"))
		seq->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0643);
	else if (ft_match(operator, "<"))
		seq->infile = open(file, O_RDONLY);
	else if (ft_match(operator, "<<"))
		seq->infile = get_heredoc_input(file);
	// NEED TO HANDLE UNKOWN FILE ERROR HERE
}

void	handle_redirections(t_ctrl_seq *seq, void **input, t_token *tokens)
{
	// TESTED
	int	i;

	i = 0;
	while (input[i] && tokens[i] != CTRL_OP)
	{
		if (tokens[i] == REDIRECT && tokens[i + 1] == FILE_)
			redirect_fd(seq, (char *)input[i], (char *)input[i + 1]);
		i++;
	}
}
