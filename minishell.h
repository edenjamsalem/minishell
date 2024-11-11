/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/11 22:53:46 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_flag; // setting up global var to be used by all files w header file included

enum							e_token
{
	TEXT,
	NUMBER,
	CMD,
	VAR,
	KEYWORD,
	S_QUOTES,
	D_QUOTES,
	PATH,
	ENV,
	CONTROL_OP, //  ||, &&, &, ;, ;;, ;&, ;;&, |, |&, (, or )
	REDIRECT,
	COMMENT,
	GLOB, // wildcard *
	NLINE,
};

typedef struct s_word
{
	char						*raw_text;
	enum e_token				token;
}								t_word;

// SIGNALS

void							handle_signal(int signum, siginfo_t *info,
									void *context);

void							setup_sig_handlers(void);

// BUILTINS

int								ft_env(t_list_2 *env_vars);

int								ft_pwd(void);

void							ft_export(t_dict *new_var, t_list_2 *envp_vars);

void							ft_unset(t_dict *var, t_list_2 **envp_vars);

void							ft_cd(char *file_path);

void							free_envp_dict(t_list_2 *envp_vars);

#endif