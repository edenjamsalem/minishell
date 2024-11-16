/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/16 11:44:37 by mganchev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include "./libft/libft.h"
# include <dirent.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

extern volatile sig_atomic_t	g_flag;
// setting up global var to be used by all files w header file included

# define IFS " \t\n"
# define QUOTES "\'\""
# define IGNORE_QUOTES true
# define INC_QUOTES true

enum							e_token
{
	TEXT,
	NUMBER,
	CMD,
	VAR,
	KEYWORD, // if, then, else etc.
	S_QUOTES,
	D_QUOTES,
	PATH,
	CONTROL_OP, //  ||, &&, &, ;, ;;, ;&, ;;&, |, |&, (, or )
	REDIRECT,
	COMMENT,
	GLOB, // wildcard *
	NLINE,
};

typedef struct s_word
{
	char						*text;
	enum e_token				token;
}								t_word;

// SIGNALS

void							handle_signal(int signum, siginfo_t *info,
									void *context);

void							setup_sig_handlers(void);

// BUILTINS

void							ft_echo(char *text, bool n_flag);

int								ft_env(t_dict *envp_vars);

int								ft_pwd(void);

void							ft_export(t_dict *new_var, t_dict **envp_vars);

void							ft_unset(t_dict *var, t_dict **envp_vars);

void							ft_cd(char *file_path);

// TOKENISATION

void							tokenise(t_list_2 *parsed_input);

bool							is_keyword(char *word);

bool							is_command(char *word);

bool							is_number(char *word);

bool							is_var(char *word);

bool							is_redirect(char *word);

// PARSE FNS

t_list_2						*word_split(char *input);

t_list_2						*parse(char *input, t_dict *envp_dict);

void							skip_spaces(char **text);

int								skip_quotes(char **text);

char							*skip_alnum(char **text);

char							*skip_word(char **text);

// PARAM/VAR EXPANSION

char							*expand_params(char *input, t_dict *envp_dict);

char							*expand_vars(char *input, t_dict *envp_dict,
									bool ignore_quotes);

static int						get_len(char *input, t_dict *envp_dict);

void							copy_quoted_text(char **input, char **expanded);

void							copy_expanded_var(char **input, char **expanded,
									t_dict *envp_dict);

// ENVP FNS

t_dict							*init_envp_dict(char **envp);

void							free_envp_dict(t_list_2 *envp_dict);

void							free_word(t_word *word);

#endif