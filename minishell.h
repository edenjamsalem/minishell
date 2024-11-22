/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/22 00:59:13 by mganchev         ###   ########.fr       */
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
# include <sys/wait.h> 

extern volatile sig_atomic_t	g_flag;
// setting up global var to be used by all files w header file included

# define IFS " \t\n"
# define QUOTES "\'\""
#define IGNORE_QUOTED_VARS 1
#define INC_QUOTED_VARS 0

typedef enum	e_token
{
	TEXT,
	QUOTED,
	CMD,
	CONTROL_OP,
	REDIRECT_OP,
	REDIRECT_FILE,
	PIPE,
} e_token;

typedef struct s_word
{
	char		*text;
	e_token		token;
}				t_word;

typedef struct s_shell
{
	t_list_2	*input; // tokenised output of parsing 
	int			**pipe_fd;	// dynamically allocated list of fd's for each pipe 
	t_list_2	*cmds;		// list of cmds to be executed in each redirected pipe (see pipex)
	bool		exit_status;
}	t_shell;

typedef enum	e_ctrl_op
{
	NONE,
	AND,
	OR,
} e_ctrl_op;

typedef struct s_cmd
{
	char		*cmd; // ptr to input->content->text (No duplication)
	t_list_2	*args; // arguments for command, also copy ptrs from input->content->text
	e_ctrl_op	condition;
}	t_cmd;


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

int		skip_quotes(char **text);

char	*skip_word(char **text);

char	*skip_while(char **text, int (*condition)(char));

char	*skip_set(char **text, char *set);

t_list_2	*word_split(char *input);

void	quote_removal(t_list_2 *input);



// PARAM EXPANSION

char	*expand_vars(char *input, t_dict *envp_dict, bool ignore_quotes);

void	expand_vars_inside_quotes(t_list_2 *input, t_dict *envp_dict);

char	*expand_params(char *input, t_dict *envp_dict); // ???

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict);

void	copy_quoted_text(char **input, char **expanded);

char	*expand_vars(char *input, t_dict *envp_dict, bool ignore_quotes);

void	copy_quoted_text(char **input, char **expanded);

void	copy_expanded_var(char **input, char **expanded, t_dict *envp_dict);


// ENVP FNS

t_dict	*init_envp_dict(char **envp);

void	free_word(t_word *word);

void	free_envp_dict(t_list_2 *envp_dict);

// EXECUTION

void	handle_redirections(t_list_2 *input, int **pipe_fd);

pid_t	pipe_fork(int pipe_fd[2]);

#endif