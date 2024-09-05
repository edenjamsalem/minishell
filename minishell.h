/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/05 16:45:01 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_var
{
	char	*key;
	char	*value;
}				t_var;

t_var	*parse_envp(char const *envp_line);

int		ft_env(t_list_2 *env_vars);

int		ft_pwd(void);

void	ft_export(t_var *new_var, t_list_2 *envp_vars);

void	free_var(t_var *var);

void	free_envp_vars(t_list_2 *envp_vars);

#endif