/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/29 17:24:30 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*find_cmd_path(char *cmd, t_dict *envp)
{
	char	**file_paths;
	char	*cmd_path;
	char	*tmp;
	int		i;

	file_paths = ft_split(get_dict_value("PATH", envp), ':');
	i = 0;
	while (file_paths[i])
	{
		tmp = ft_strjoin(file_paths[i++], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free (tmp);
		if (access(cmd_path, F_OK) != -1)
		{
			FREE_2DARR(file_paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	FREE_2DARR(file_paths);
	return (NULL);
}

void	ft_exec(char **cmd, t_dict *envp)
{
	char	*cmd_path;
	pid_t	pid; 

	cmd_path = find_cmd_path(cmd[0], envp);
	if (execve(cmd_path, cmd, NULL) == -1)
	{
		perror("execve");		// NEED TO CHECK IF THIS ERROR CHECK IS STILL VALID	
		exit(EXIT_FAILURE);
	}
}

int	builtin(char **cmd, t_dict *envp) // NEED TO CHECK ABOUT EXIT STATUS FOR BUILTINS
{
	if (MATCH(cmd[0], "env"))
		return (ft_env(envp));
	else if (MATCH(cmd[0], "cd"))
		return (ft_cd(cmd));
	else if (MATCH(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (MATCH(cmd[0], "export"))
		return (ft_export(cmd, envp));
	else if (MATCH(cmd[0], "pwd"))
		return (ft_pwd());
	else if (MATCH(cmd[0], "unset"))
		return (ft_unset(cmd, envp));
	return (0);
}