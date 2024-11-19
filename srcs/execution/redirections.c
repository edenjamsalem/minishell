/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:31:16 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/19 17:52:04 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if words succeeding redirection symbols are more than 1 word long 
// post-expansions we report an error

int	**allocate_pipe_fd(int size)
{
	int	i;
	int	**pipe_fd;

	if (size < 1)
		return (NULL);
	pipe_fd = malloc(sizeof(int *) * (size + 1));
	if (!pipe_fd)
		return (NULL);
	i = 0;
	while (i < size)
	{
		pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pipe_fd[i])
		{
			free_2darr((void *)pipe_fd, i - 1);
			return (NULL);
		}
		i++;
	}
	pipe_fd[size] = NULL;
	return (pipe_fd);
}

int	get_here_doc_input(char *delimiter)
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
			if (MATCH(input, delimiter))
				exit(EXIT_SUCCESS);
			write(pipe_fd[1], input, bytes_read);
		}
	}
	close(pipe_fd[1]);
	wait(0);
	return (pipe_fd[0]);
}

void	redirect_fd(char *operator, char *arg)
{
	int	fd;

	if (MATCH(operator, ">"))
	{
		fd = open(arg, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (MATCH(operator, ">>"))
	{	
		fd = open(arg, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (MATCH(operator, "<"))
	{
		fd = open(arg, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (MATCH(operator, "<<"))
	{
		fd = get_here_doc_input(arg);		
		dup2(fd, STDIN_FILENO);
	}
}

void	redirect_file(char *word)
{
	char	*operator;
	char	*arg;
	
	operator = ft_strcut(word, skip_op(word));
	arg = ft_strcut(word, skip_word(word));
	redirect_fd(operator, arg);
	free(operator);
	free(arg);
}

void	handle_redirections(t_list_2 *input, int **pipe_fd)
{
	t_word	*word;
	t_word	*arg;
	int		pipe_count;
	
	while (input)
	{
		word = (t_word *)(input->content);
		arg = (t_word *)(input->next);
		if (word->token == REDIRECT_OP)
			redirect_fd(word->text, arg);
		else if (word->token == REDIRECT_FILE)
			redirect_file(word->text);
		else if (word->token == PIPE)
			pipe_count++;		
		input = input->next;
	}
	pipe_fd = allocate_pipe_fd(pipe_count);
}