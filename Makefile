# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:01:35 by eamsalem          #+#    #+#              #
#    Updated: 2024/12/20 16:59:16 by eamsalem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(MINIDIR)/minishell
MINIDIR = $(HOME)/bin

CFLAGS = -Wall -Werror -Wextra -g3

OBJDIR = ./build
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFTDIR = ../libft
LIBFT = $(LIBFTDIR)/libft.a
LIBS = $(LIBFT) -lreadline

SRCDIR = srcs
PARSEDIR = $(SRCDIR)/parser
INITDIR = $(SRCDIR)/init_fns
EXECDIR	= $(SRCDIR)/execution
TOKENDIR = $(SRCDIR)/tokeniser
BUILTINDIR = $(SRCDIR)/builtins

SRCS =	$(SRCDIR)/minishell.c \
		$(SRCDIR)/signals.c \
		$(SRCDIR)/cleanup.c \
		$(SRCDIR)/utils.c \
\
		$(PARSEDIR)/expansions.c \
		$(PARSEDIR)/parse.c \
		$(PARSEDIR)/check_fns.c \
		$(PARSEDIR)/parse_utils.c \
		$(PARSEDIR)/skip_fns.c \
		$(PARSEDIR)/wildcard.c \
		$(PARSEDIR)/word_split.c \
\
		$(INITDIR)/init_ctrl_seq.c \
		$(INITDIR)/init_cmd_seq.c \
		$(INITDIR)/redirections.c \
\
		$(EXECDIR)/exec_ctrl_seq.c \
		$(EXECDIR)/exec_cmd_seq.c \
		$(EXECDIR)/exec_utils.c \
		$(EXECDIR)/pipe_fns.c \
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

$(MINIDIR):
	mkdir -p $(MINIDIR)

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