# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:01:35 by eamsalem          #+#    #+#              #
#    Updated: 2025/01/07 23:17:43 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Werror -Wextra -g3

OBJDIR = ./build
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFTDIR = ./includes/libft
LIBFT = $(LIBFTDIR)/libft.a
LIBS = $(LIBFT) -lreadline

SRCDIR = srcs
PARSEDIR = $(SRCDIR)/parser
INITDIR = $(SRCDIR)/init_fns
EXECDIR	= $(SRCDIR)/execution
TOKENDIR = $(SRCDIR)/tokeniser
BUILTINDIR = $(SRCDIR)/builtins

SRCS =	$(SRCDIR)/main.c \
		$(SRCDIR)/utils.c \
		$(SRCDIR)/signals.c \
		$(SRCDIR)/cleanup.c \
		$(SRCDIR)/ctrl_op_syntax_check.c \
\
		$(PARSEDIR)/expansions.c \
		$(PARSEDIR)/parse.c \
		$(PARSEDIR)/parse_utils.c \
		$(PARSEDIR)/skip_fns.c \
		$(PARSEDIR)/wildcard.c \
		$(PARSEDIR)/word_split.c \
\
		$(INITDIR)/init_ctrl_seq.c \
		$(INITDIR)/init_cmd_seq.c \
		$(INITDIR)/init_shell.c \
		$(INITDIR)/init_utils.c \
		$(INITDIR)/redirections.c \
\
		$(EXECDIR)/exec_ctrl_seq.c \
		$(EXECDIR)/exec_cmd_seq.c \
		$(EXECDIR)/exec_utils.c \
		$(EXECDIR)/exec_pipe.c \
\
		$(TOKENDIR)/grammar_check.c \
		$(TOKENDIR)/tokenisation.c \
		$(TOKENDIR)/token_utils.c \
\
		$(BUILTINDIR)/env.c \
		$(BUILTINDIR)/pwd.c \
		$(BUILTINDIR)/cd.c \
		$(BUILTINDIR)/export.c \
		$(BUILTINDIR)/unset.c \
		$(BUILTINDIR)/echo.c \
		$(BUILTINDIR)/exit.c \

all: $(NAME) $(OBJS) $(LIBFT) $(MINIDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(@D)
	cc $(CFLAGS) -c $< -o $@

$(OBJDIR)/parser/%.o: $(SRCDIR)/parser/%.c
	mkdir -p $(@D)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJDIR) $(OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(LIBS) -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBFT):
	make -C $(LIBFTDIR) all

clean:
	make -C $(LIBFTDIR) clean
	rm -fr $(OBJDIR)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re