# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/26 10:40:04 by user              #+#    #+#              #
#    Updated: 2025/01/02 16:17:16 by eamsalem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Werror -Wextra

OBJDIR =./build

STRDIR = ./str_fns
CHRDIR = ./chr_fns
LSTDIR = ./lst_fns
ARRLSTDIR = ./arrlst_fns
LST2DIR = ./lst_2fns
INTLSTDIR = ./int_lst_fns
INTARRDIR = ./int_arr_fns
MEMDIR = ./mem_fns
PRINTDIR = ./print_fns
DICTDIR = ./dict_fns

SRCS =	$(STRDIR)/ft_split.c \
		$(STRDIR)/ft_split_set.c \
		$(STRDIR)/ft_strchr.c \
		$(STRDIR)/ft_strchrset.c \
		$(STRDIR)/ft_strdup.c \
		$(STRDIR)/ft_striteri.c \
		$(STRDIR)/ft_strjoin.c \
		$(STRDIR)/ft_strlcat.c \
		$(STRDIR)/ft_strlcpy.c \
		$(STRDIR)/ft_strlen.c \
		$(STRDIR)/ft_strmapi.c \
		$(STRDIR)/ft_strncmp.c \
		$(STRDIR)/ft_strnstr.c \
		$(STRDIR)/ft_strrchr.c \
		$(STRDIR)/ft_strtrim.c \
		$(STRDIR)/ft_substr.c \
		$(STRDIR)/ft_strtrunc_front.c \
		$(STRDIR)/ft_strunion.c \
		$(STRDIR)/ft_strcut.c \
		$(STRDIR)/ft_match.c \
\
		$(CHRDIR)/ft_isalnum.c \
		$(CHRDIR)/ft_isalpha.c \
		$(CHRDIR)/ft_isascii.c \
		$(CHRDIR)/ft_isdigit.c \
		$(CHRDIR)/ft_isspace.c \
		$(CHRDIR)/ft_isprint.c \
		$(CHRDIR)/chrsetcmp.c \
		$(CHRDIR)/ft_issign.c \
		$(CHRDIR)/ft_tolower.c \
		$(CHRDIR)/ft_toupper.c \
\
		$(LSTDIR)/ft_lstadd_back.c \
		$(LSTDIR)/ft_lstadd_front.c \
		$(LSTDIR)/ft_lstclear.c \
		$(LSTDIR)/ft_lstdelone.c \
		$(LSTDIR)/ft_lstiter.c \
		$(LSTDIR)/ft_lstlast.c \
		$(LSTDIR)/ft_lstmap.c \
		$(LSTDIR)/ft_lstnew.c \
		$(LSTDIR)/ft_lstsize.c \
\
		$(LST2DIR)/ft_lst_2add_back.c \
		$(LST2DIR)/ft_lst_2last.c \
		$(LST2DIR)/ft_del_lst_2node.c \
		$(LST2DIR)/ft_lst_2new.c \
		$(LST2DIR)/ft_lst_2delone.c \
		$(LST2DIR)/ft_lst_2clear.c \
\
		$(INTLSTDIR)/int_lst_to_arr.c \
		$(INTLSTDIR)/int_lstnew.c \
		$(INTLSTDIR)/int_lstadd_back.c \
		$(INTLSTDIR)/int_lstadd_front.c \
		$(INTLSTDIR)/int_lstdel_front.c \
		$(INTLSTDIR)/int_lstlast.c \
		$(INTLSTDIR)/int_lstsize.c \
		$(INTLSTDIR)/int_lstclear.c \
\
		$(ARRLSTDIR)/arrlst_fns.c \
\
		$(INTARRDIR)/int_arrdup.c \
		$(INTARRDIR)/intsetcmp.c \
		$(INTARRDIR)/int_arrtrunc.c \
		$(INTARRDIR)/int_arrlcpy.c \
\
		$(MEMDIR)/ft_bzero.c \
		$(MEMDIR)/ft_calloc.c \
		$(MEMDIR)/ft_memchr.c \
		$(MEMDIR)/ft_memcmp.c \
		$(MEMDIR)/ft_memcpy.c \
		$(MEMDIR)/ft_memmove.c \
		$(MEMDIR)/ft_memset.c \
\
		$(PRINTDIR)/ft_putchar_fd.c \
		$(PRINTDIR)/ft_putendl_fd.c \
		$(PRINTDIR)/ft_putnbr_fd.c \
		$(PRINTDIR)/ft_putstr_fd.c \
		$(PRINTDIR)/ft_putaddr.c \
		$(PRINTDIR)/ft_putaddr_fd.c \
		$(PRINTDIR)/ft_putchar.c \
		$(PRINTDIR)/ft_putnbr_base.c \
		$(PRINTDIR)/ft_putnbr_base_fd.c \
		$(PRINTDIR)/ft_putnbr.c \
		$(PRINTDIR)/ft_putstr.c \
		$(PRINTDIR)/ft_putuslong_base.c \
		$(PRINTDIR)/ft_putuslong_base_fd.c \
		$(PRINTDIR)/ft_putusnbr.c \
		$(PRINTDIR)/ft_putusnbr_fd.c \
		$(PRINTDIR)/ft_printf.c \
		$(PRINTDIR)/ft_fprintf.c \
\
		$(DICTDIR)/str_to_dict.c \
		$(DICTDIR)/free_dict.c \
		$(DICTDIR)/get_dict_value.c \
		$(DICTDIR)/set_dict_value.c \
		$(DICTDIR)/get_dict_entry.c \
		$(DICTDIR)/dict_addback.c \
		$(DICTDIR)/dict_last.c \
		$(DICTDIR)/dict_clear.c \
		$(DICTDIR)/dict_size.c \
		$(DICTDIR)/dict_to_arr.c \
		$(DICTDIR)/del_dict_node.c \
		$(DICTDIR)/print_dict.c \
\
		ft_atoi.c \
		ft_itoa.c \
		ft_swap.c \
		bubble_sort.c \
		free_2darr.c \
		ft_2darr_len.c	\
		skip_fns.c	\
		ft_atol.c \
		ft_atoi_base.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

${NAME}: $(OBJS) 
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME) a.out

re: fclean all

.PHONY: all clean fclean re bonus
