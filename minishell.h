/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/18 16:56:40 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include "../libft/libft.h"
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
#define IGNORE_QUOTED_VARS 1
#define INC_QUOTED_VARS 0

typedef enum	e_token
{
	TEXT,
	NUMBER,
	CMD,
	VAR,
	KEYWORD, // if, then, else etc.
	S_QUOTES,
	D_QUOTES,
	PATH,
	ENV,
	CONTROL_OP, //  ||, &&, &, ;, ;;, ;&, ;;&, |, |&, (, or )
	REDIRECT,
	COMMENT,
	GLOB, // wildcard *
	NLINE,
} e_token;

typedef struct s_word
{
	char		*text;
	e_token		token;
}				t_word;


// SIGNALS

void	handle_signal(int signum, siginfo_t *info, void *context);

void	setup_sig_handlers(void);


// BUILTINS

void	ft_echo(char *text, bool n_flag);

int		ft_env(t_dict *envp_vars);

int		ft_pwd(void);

void	ft_export(t_dict *new_var, t_dict **envp_vars);

void	ft_unset(t_dict *var, t_dict **envp_vars);

void	ft_cd(char *file_path);

void	ft_cd(char *file_path);

// PARSE FNS

t_list_2	*word_split(char *input);

t_list_2	*parse(char *input, t_dict *envp_dict);

void	skip_spaces(char **text);

int		skip_quotes(char **text);

char	*skip_alnum(char **text);

char	*skip_word(char **text);

t_list_2	*word_split(char *input);

void	quote_removal(t_list_2 *input);



// PARAM EXPANSION

char	*expand_vars(char *input, t_dict *envp_dict, bool ignore_quotes);

void	expand_vars_inside_quotes(t_list_2 *input, t_dict *envp_dict);

char	*expand_params(char *input, t_dict *envp_dict); // ???

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict);

void	copy_quoted_text(char **input, char **expanded);

char	*expand_vars(char *input, t_dict *envp_dict, bool ignore_quotes);

// static int						get_len(char *input, t_dict *envp_dict);

void	copy_quoted_text(char **input, char **expanded);

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict);

// ENVP FNS

t_dict	*init_envp_dict(char **envp);


void	free_word(t_word *word);


void							free_envp_dict(t_list_2 *envp_dict);

#endif