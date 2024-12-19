/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 10:42:47 by eamsalem          #+#    #+#             */
/*   Updated: 2024/12/06 16:22:19by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _DEFAULT_SOURCE
#  define _DEFAULT_SOURCE
# endif

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define IFS " \t\n"
# define QUOTES "\'\""

typedef enum e_token
{
	END,
	TEXT,
	CMD,
	FILE_,
	REDIRECT,
	PIPE,
}				t_token;

typedef enum e_ctrl_op
{
	NONE,
	AND,
	OR,
}				t_ctrl_op;

typedef enum e_error
{
	SYNTAX,
	CMD_,
	DIRECT,
}				t_error;

typedef struct s_cmd_seq
{
	t_arrlst	*words;
	t_token		*tokens;
	char ***cmds;  // list of 2d char arrays with command + flags + args
	int **pipe_fd; // dynamically allocated list of fd's for each pipe
	int			pipe_count;
	int			infile;
	int			outfile;
}				t_cmd_seq;

typedef struct s_ctrl_seq // CONTROL SEQUENCE
{
	char *raw_input;
	t_ctrl_op ctrl_op;
	bool inside_braces;
	int exit_status;

}				t_ctrl_seq;

// SIGNALS

void			handle_signal(int signum, siginfo_t *info, void *context);

void			setup_sig_handler(int signum);

void			handle_ctrl_d(int bytes_read, int line_count, char *eof);

void			handle_ctrl_c(void);

void			handle_ctrl_c_child(int signum);

// BUILTINS

int				ft_env(t_dict *envp_vars);

int				ft_pwd(void);

int				ft_export(char **cmd, t_dict *envp_vars);

int				ft_unset(char **cmd, t_dict *envp_vars);

int				ft_cd(char **cmd);

int				ft_echo(char **cmd);

void			ft_exit(char **cmd_argv, bool inside_main_process);

// PARSE FNS

t_ctrl_seq		**gen_ctrl_seq(char *input);

t_arrlst		*word_split(char *input);

void			parse(char *input, t_cmd_seq *command, t_dict *envp_dict);

int				skip_quotes(char **text);

char			*skip_while(char **text, int (*condition)(char));

char			*skip_set(char **text, char *set);

char			*skip_to(char **text, char *set);

char			*skip_len(char **text, int size);

void			quote_removal(t_arrlst *input);

bool			contains(char *word, char *set);

void			remove_quotes(char *text);

void			del_char(char *text);

// PARAM EXPANSION

char			*expand_vars(char *input, t_dict *envp, bool ign_double,
					bool ign_single);

void							expand_vars_in_double_quotes(void **input, t_dict *envp_dict);

void			copy_expanded_var(char **input, char **expanded,
					t_dict *envp_dict);

void			copy_quoted_text(char **input, char **expanded);

void			copy_quoted_text(char **input, char **expanded);

void			copy_expanded_var(char **input, char **expanded,
					t_dict *envp_dict);

void			expand_wildcard(t_arrlst *words, const char *pattern);

// INIT FNS

t_dict			*init_envp_dict(char **envp);

t_cmd_seq		*gen_cmd_seq(char *input, t_dict *envp);

// TOKENISER

int				find_next_token(t_token *tokens, enum e_token ref);

t_token			get_prev_token(t_token *tokens, int index);

t_token			*primary_tokenisation(t_arrlst *words, t_token *tokens);

t_token			*secondary_tokenisation(t_arrlst *words, t_token *tokens);

t_token			*tokenise(t_arrlst *words);

bool			is_redirect(void *word);

bool			is_file(int index, t_token *tokens);

bool			is_command(int index, t_token *tokens);

bool			is_control(void *word);

bool			is_pipe(void *word);

int				grammar_check(t_arrlst *words, t_token *tokens);

bool			is_repeat(t_token *tokens, int *index);

bool			is_file_name(t_arrlst *words, t_token *tokens, int *index);

bool			is_start(t_token *tokens, int *index);

bool			is_redirect_correct(t_token *tokens, int *index);

int				ft_perror(t_error type, char *error_msg);

int				skip_redirect(t_token *tokens, int index);

// EXECUTION

int				execute(t_ctrl_seq **ctrl_seq, t_dict *envp);

void			assign_redirections(t_cmd_seq *command, t_dict *envp);

pid_t			pipe_fork(int pipe_fd[2]);

pid_t			ft_fork(void);

void			exec_infile_to_pipe(int pipe_fd[2], char **cmd, t_dict *envp);

void			exec_pipe_to_pipe(int *prev_pipe_fd, int *pipe_fd, char **cmd,
					t_dict *envp);

void			exec_pipe_to_outfile(int pipe_fd[2], char **cmd, t_dict *envp);

void			ft_exec(char **cmd, t_dict *envp);

t_ctrl_seq		**gen_ctrl_seq(char *input);

int				exec_builtin(char **cmd, t_dict *envp,
					bool inside_main_process);

int				is_builtin(char *cmd);

void			setup_pipes(t_cmd_seq *command);

void			assign_pipe_count(t_cmd_seq *command);

void			assign_cmds(t_cmd_seq *command);

// TEST FUNCTIONS; can remove those later

void			print_arrlst(t_arrlst *list);

char			*token_to_string(t_token token);

void			print_tokens(t_arrlst *words, t_token *tokens);

void			print_ctrl_seq(t_ctrl_seq **ctrl_seq);

#endif