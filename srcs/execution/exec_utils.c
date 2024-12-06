/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 15:52:10 by eamsalem         ###   ########.fr       */
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

int	builtin(char **cmd, t_dict *envp)
{
	if (!cmd || !(*cmd))
		return (0);
	else if (ft_match(cmd[0], "env"))
		return (ft_env(envp));
	else if (ft_match(cmd[0], "cd"))
		return (ft_cd(cmd));
	else if (ft_match(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (ft_match(cmd[0], "export"))
		return (ft_export(cmd, envp));
	else if (ft_match(cmd[0], "pwd"))
		return (ft_pwd());
	else if (ft_match(cmd[0], "unset"))
		return (ft_unset(cmd, envp));
	else if (ft_match(cmd[0], "exit"))
		ft_exit(cmd, false);
	return (0);
}

void	ft_exec(char **cmd, t_dict *envp)
{
	char	*cmd_path;

	if (!cmd || !(*cmd))
		exit(EXIT_SUCCESS);
	if (ft_match(cmd[0], "exit"))
		ft_exit(cmd, true);
	if (builtin(cmd, envp))
		exit(EXIT_SUCCESS);
	cmd_path = find_cmd_path((char *)cmd[0], envp);
	if (execve(cmd_path, cmd, dict_to_arr(envp)) == -1)
	{
		ft_fprintf(2, "%s: command not found\n", cmd[0]);	
		exit(EXIT_FAILURE);
	}
}
