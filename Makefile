# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 14:01:35 by eamsalem          #+#    #+#              #
#    Updated: 2024/11/16 13:40:37 by mganchev         ###   ########.fr        #
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
BUILTINDIR = $(SRCDIR)/builtins

SRCS =	$(SRCDIR)/minishell.c \
		$(SRCDIR)/signals.c \
		$(SRCDIR)/envp_utils.c \
		$(SRCDIR)/parser/expansions.c \
		$(SRCDIR)/parser/expansions_utils.c \
		$(SRCDIR)/parser/param_expansion.c \
		$(SRCDIR)/parser/parse.c \
		$(SRCDIR)/parser/parse_utils.c \
		$(SRCDIR)/parser/tokenisation.c \
		$(SRCDIR)/parser/token_utils.c \
		$(SRCDIR)/parser/wildcard.c \
		$(SRCDIR)/parser/word_split.c \
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