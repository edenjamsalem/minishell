/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/09 14:00:02 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

t_dict	*str_to_dict(char const *envp_line);

int		ft_env(t_list_2 *env_vars);

int		ft_pwd(void);

void	ft_export(t_dict *new_var, t_list_2 *envp_vars);

void	ft_unset(t_dict *var, t_list_2 **envp_vars);

void	ft_cd(char *file_path);

void	free_envp_vars(t_list_2 *envp_vars);

#endif