/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/20 15:01:39 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
			free_2darr((void **)file_paths, ft_2darr_len((void **)file_paths));
			return (ft_strdup(cmd_path));
		}
		i++;
	}
	ft_fprintf(2, "bash: %s: No such file or directory\n", cmd);
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

int	exec_builtin(t_shell *mini, char **cmd, bool in_main)
{
	if (!cmd || !(*cmd))
		return (0);
	else if (ft_match(cmd[0], "env"))
		return (ft_env(mini->envp));
	else if (ft_match(cmd[0], "cd"))
		return (ft_cd(cmd));
	else if (ft_match(cmd[0], "echo"))
		return (ft_echo(cmd));
	else if (ft_match(cmd[0], "export"))
		return (ft_export(cmd, mini->envp));
	else if (ft_match(cmd[0], "pwd"))
		return (ft_pwd());
	else if (ft_match(cmd[0], "unset"))
		return (ft_unset(cmd, mini->envp));
	else if (ft_match(cmd[0], "exit"))
		ft_exit(mini, cmd, in_main);
	return (0);
}

void	ft_exec(t_shell *mini, char **cmd)
{
	char	*cmd_path;

	if (!cmd || !(*cmd))
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd[0]))
	{
		exec_builtin(mini, cmd, false);
		exit(EXIT_SUCCESS);
	}
	cmd_path = get_cmd_path((char *)cmd[0], mini->envp);
	if (!cmd_path)
		exit(2);
	signal(SIGINT, handle_ctrl_c_child);
	signal(SIGQUIT, handle_ctrl_c_child);
	if (execve(cmd_path, cmd, dict_to_arr(mini->envp)) == -1)
	{
		ft_fprintf(2, "%s: command not found\n", cmd[0]);	
		exit(127);
	}
}
