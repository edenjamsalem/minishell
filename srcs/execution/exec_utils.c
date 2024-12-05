/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:34:48 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/05 17:12:38 by eamsalem         ###   ########.fr       */
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
	int		i = 0;

	if (builtin(cmd, envp))
		exit(EXIT_SUCCESS);
	cmd_path = find_cmd_path((char *)cmd[0], envp);
/*	ft_printf("cmd = %s\n", cmd[0]);
	ft_printf("cmd path = %s\n", cmd_path);
	while (cmd[i])
	{
		ft_printf("%s ", cmd[i++]);
	}*/	
	if (execve(cmd_path, cmd, dict_to_arr(envp)) == -1)
	{
		perror("execve");	// NEED TO CHECK IF THIS ERROR CHECK IS STILL VALID	
		exit(EXIT_FAILURE);
	}
}
