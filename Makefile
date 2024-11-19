# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:01:35 by eamsalem          #+#    #+#              #
#    Updated: 2024/11/19 14:12:15 by eamsalem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = $(MINIDIR)/minishell
MINIDIR = $(HOME)/bin

CFLAGS = -Wall -Werror -Wextra -g3

OBJDIR = ./build
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LIBFTDIR = ./libft
LIBFT = $(LIBFTDIR)/libft.a
LIBS = $(LIBFT) -lreadline

SRCDIR = srcs
PARSEDIR = $(SRCDIR)/parser
EXECDIR	= $(SRCDIR)/execution
BUILTINDIR = $(SRCDIR)/builtins

SRCS =	$(SRCDIR)/minishell.c \
		$(SRCDIR)/signals.c \
		$(SRCDIR)/envp_utils.c \
		$(PARSEDIR)/expansions.c \
		$(PARSEDIR)/parse.c \
		$(PARSEDIR)/parse_utils.c \
		$(PARSEDIR)/param_expansion.c \
		$(PARSEDIR)/skip_fns.c \
		$(PARSEDIR)/tokenisation.c \
		$(PARSEDIR)/token_utils.c \
		$(PARSEDIR)/wildcard.c \
		$(PARSEDIR)/word_split.c \
		$(BUILTINDIR)/env.c \
		$(BUILTINDIR)/pwd.c \
		$(BUILTINDIR)/cd.c \
		$(BUILTINDIR)/export.c \
		$(BUILTINDIR)/unset.c \
		$(BUILTINDIR)/echo.c

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