/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 13:34:48 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_flag; // setting up global var to be used by all files w header file included

#define SPACES " \t\n"

enum	e_token
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
	char			*text;
	enum e_token	token;
}	t_word;


// SIGNALS

void		handle_signal(int signum, siginfo_t *info, void *context);

void		setup_sig_handlers(void);


// BUILTINS

int			ft_env(t_dict *envp_vars);

int			ft_pwd(void);

void		ft_export(t_dict *new_var, t_dict **envp_vars);

void		ft_unset(t_dict *var, t_dict **envp_vars);

void		ft_cd(char *file_path);

// PARSE FNS

void		skip_spaces(char **text);

int			skip_quotes(char **text, char quote);

char		*skip_word(char **text);


// ENVP FNS

t_dict		*init_envp_dict(char **envp);

void		free_envp_dict(t_list_2 *envp_dict);


#endif