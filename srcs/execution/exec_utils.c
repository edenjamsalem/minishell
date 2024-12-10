/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/10 15:53:19 by eamsalem         ###   ########.fr       */
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

int	is_builtin(char **cmd)
{
	if (!cmd || !(*cmd))
		return (0);
	else if (ft_match(cmd[0], "env"))
		return (1);
	else if (ft_match(cmd[0], "cd"))
		return (1);
	else if (ft_match(cmd[0], "echo"))
		return (1);
	else if (ft_match(cmd[0], "export"))
		return (1);
	else if (ft_match(cmd[0], "pwd"))
		return (1);
	else if (ft_match(cmd[0], "unset"))
		return (1);
	else if (ft_match(cmd[0], "exit"))
		return (1);
	return (0);
}

int	exec_builtin(char **cmd, t_dict *envp, bool inside_main_process)
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
		ft_exit(cmd, inside_main_process);
	return (0);
}

void	ft_exec(char **cmd, t_dict *envp)
{
	char	*cmd_path;

	if (!cmd || !(*cmd))
		exit(EXIT_SUCCESS);
	if (exec_builtin(cmd, envp, false))
		exit(EXIT_SUCCESS);
	cmd_path = find_cmd_path((char *)cmd[0], envp);
	if (execve(cmd_path, cmd, dict_to_arr(envp)) == -1)
	{
		ft_fprintf(2, "%s: command not found\n", cmd[0]);	
		exit(EXIT_FAILURE);
	}
	
}
