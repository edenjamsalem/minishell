/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:48 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/07 16:25:58 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	pipe_fork(int pipe_fd[2])
{
	pid_t	pid;

	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_ctrl_c_child);
		signal(SIGQUIT, handle_ctrl_c_child);
	}
	return (pid);
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		signal(SIGINT, handle_ctrl_c_child);
		signal(SIGQUIT, handle_ctrl_c_child);
	}
	return (pid);
}

static char	*get_cmd_path(char *cmd, t_dict *envp)
{
	char	**file_paths;
	char	cmd_path[4096];
	int		i;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	file_paths = ft_split(get_dict_value("PATH", envp), ':');
	i = 0;
	while (file_paths && file_paths[i])
	{
		cmd_path[0] = '\0';
		ft_strlcat(cmd_path, file_paths[i], 4096);
		ft_strlcat(cmd_path, "/", 4096);
		ft_strlcat(cmd_path, cmd, 4096);
		if (access(cmd_path, F_OK) != -1)
		{
			free_2darr((void **)file_paths, i - 1);
			return (ft_strdup(cmd_path));
		}
		i++;
	}
	free_2darr((void **)file_paths, ft_2darr_len((void **)file_paths));
	return (NULL);
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	else if (ft_match(cmd, "env"))
		return (1);
	else if (ft_match(cmd, "cd"))
		return (1);
	else if (ft_match(cmd, "echo"))
		return (1);
	else if (ft_match(cmd, "export"))
		return (1);
	else if (ft_match(cmd, "pwd"))
		return (1);
	else if (ft_match(cmd, "unset"))
		return (1);
	else if (ft_match(cmd, "exit"))
		return (1);
	return (0);
}

void	ft_exec(t_shell *mini, char **cmd)
{
	char	*cmd_path;

	if (!cmd || !(*cmd))
		return (free_shell(mini), exit(EXIT_SUCCESS));
	if (is_builtin(cmd[0]))
	{
		exec_builtin(mini, cmd, false);
		free_shell(mini);
		exit(EXIT_SUCCESS);
	}
	cmd_path = get_cmd_path((char *)cmd[0], mini->envp);
	if (!cmd_path)
	{
		ft_perror(DIRECT, cmd[0]);
		free_shell(mini);
		exit(2);
	}
	signal(SIGINT, handle_ctrl_c_child);
	signal(SIGQUIT, handle_ctrl_c_child);
	if (execve(cmd_path, cmd, dict_to_arr(mini->envp)) == -1)
	{
		ft_perror(CMD_, cmd[0]);
		free_shell(mini);
		exit(127);
	}
}
