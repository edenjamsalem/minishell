/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 12:45:22 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:30:01 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H

# define LIBFT_H

# include <stddef.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h> 
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>

# define HEX "0123456789abcdef"
# define HEX_CAP "0123456789ABCDEF"

int			ft_isalpha(char c);

int			ft_isdigit(char c);

int			ft_isalnum(char c);

int			ft_isprint(int c);

int			ft_issign(char c);

int			ft_isspace(char c);

size_t		ft_strlcpy(char *dest, const char *src, size_t size);

size_t		ft_strlen(const char *str);

size_t		ft_strlcat(char *dest, const char *src, size_t size);

int			ft_toupper(int c);

int			ft_tolower(int c);

const char	*ft_strrchr(const char *s, int c);

const char	*ft_strchr(const char *s, int c);

int			ft_strncmp(const char *s1, const char *s2, size_t n);

void		*ft_memcpy(void *dest, const void *src, size_t n);

const char	*ft_strnstr(const char *big, const char *little, size_t len);

int			ft_atoi(const char *str);

void		*ft_memset(void *s, int c, size_t n);

void		*ft_bzero(void *s, size_t n);

void		*ft_memchr(const void *s, int c, size_t n);

int			ft_memcmp(const void *s1, const void *s2, size_t n);

void		*ft_calloc(size_t nmemb, size_t size);

int			ft_isascii(int c);

char		*ft_strdup(const char *s);

void		*ft_memmove(void *dest, const void *src, size_t n);

char		*ft_substr(char const *s, unsigned int start, size_t len);

char		*ft_strjoin(char const *s1, char const *s2);

char		*ft_strtrim(char const *s1, char const *set);

char		**ft_split(char const *s, char c);

char		*ft_itoa(int n);

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));

void		ft_striteri(char *s, void (*f)(unsigned int, char*));

int			ft_putchar_fd(int fd, char c);

int			ft_putstr_fd(int fd, char *str);

void		ft_putendl_fd(char *s, int fd);

int			ft_putnbr_fd(int fd, int nbr);

int			ft_putaddr_fd(int fd, void *ptr);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list		*ft_lstnew(void *content);

void		ft_lstadd_front(t_list **lst, t_list *new);

int			ft_lstsize(t_list *lst);

t_list		*ft_lstlast(t_list *lst);

void		ft_lstadd_back(t_list **lst, t_list *new);

void		ft_lstdelone(t_list *lst, void (*del)(void *));

void		ft_lstclear(t_list **lst, void (*del)(void *));

void		ft_lstiter(t_list *lst, void (*f)(void *));

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

int			chrsetcmp(char c, char *set);

int			intsetcmp(int c, int *set, int size);

int			ft_putaddr(void *ptr);

int			ft_putaddr_fd(int fd, void *ptr);

int			ft_putchar(char c);

int			ft_putchar_fd(int fd, char c);

int			ft_putnbr_base(unsigned int nbr, char *base);

int			ft_putnbr_base_fd(int fd, unsigned int nbr, char *base);

int			ft_putnbr(int nbr);

int			ft_putnbr_fd(int fd, int nbr);

int			ft_putstr(char *str);

int			ft_putuslong_base(unsigned long nbr, char *base);

int			ft_putuslong_base_fd(int fd, unsigned long nbr, char *base);

int			ft_putusnbr(unsigned int n);

int			ft_putusnbr_fd(int fd, unsigned int n);

int			ft_printf(const char *format, ...);

int			ft_fprintf(int fd, const char *format, ...);

int			*int_arrlcpy(int *dest, int *src, int size);

int			*int_arrtrunc(int *src, int size);

typedef struct s_int_lst
{
	int					content;
	struct s_int_lst	*next;
	struct s_int_lst	*prev;
}	t_int_lst;

t_int_lst	*int_lstnew(int content);

void		int_lstadd_front(t_int_lst **lst, t_int_lst *new);

int			int_lstsize(t_int_lst *lst);

t_int_lst	*int_lstlast(t_int_lst *lst);

void		int_lstadd_back(t_int_lst **lst, t_int_lst *new);

void		int_lstdelone(t_int_lst *lst);

void		int_lstdel_front(t_int_lst **lst);

void		int_lstclear(t_int_lst **lst);

int			*int_lst_to_arr(t_int_lst *lst, int size);

void		ft_swap(int *a, int *b);

void		bubble_sort_arr(int *arr, int size);

void		rev_bubble_sort_arr(int *arr, int size);

void		free_2darr(void **arr, int len);

int			ft_2darr_len(void **arr);

char		*get_next_line(int fd);

char		*ft_strtrunc_front(char *str, unsigned int chr_count);

long		ft_atol(const char *str);

int			ft_atoi_base(char *str, char *base);

typedef struct s_list_2
{
	void			*content;
	struct s_list_2	*next;
	struct s_list_2	*prev;
}	t_list_2;

t_list_2	*ft_lst_2last(t_list_2 *lst);

t_list_2	*ft_lst_2new(void *content);

void		ft_lst_2add_back(t_list_2 **lst, t_list_2 *new);

void		ft_del_lst_2node(t_list_2 **node, void (*del)(void *));

void		ft_lst_2delone(t_list_2 *lst, void (*del)(void *));

void		ft_lst_2clear(t_list_2 **lst, void (*del)(void *));

typedef struct s_dict
{
	char			*key;
	char			*value;
	struct s_dict	*next;
	struct s_dict	*prev;
}				t_dict;

void		free_dict(t_dict *dict);

t_dict		*str_to_dict(char *str);

char		**ft_split_set(char const *str, char *set);

char		*ft_strunion(char **str_arr);

char		*get_dict_value(char *key, t_dict *dict);

void		dict_addback(t_dict **dict, t_dict *new);

t_dict		*dict_last(t_dict *dict);

char		*ft_strcut(char *start, char *end);

t_dict		*get_dict_entry(char *key, t_dict *dict);

void		del_dict_node(t_dict **node);

void		dict_clear(t_dict **dict);

int			dict_size(t_dict *dict);

char		**dict_to_arr(t_dict *dict);

void		set_dict_value(char *key, char *new_value, t_dict *dict);

char		*ft_strchrset(char *str, char *set);

void		print_dict(t_dict *dict);

typedef struct s_arrlist
{
	void	**content;
	int		count;
	int		capacity;
}	t_arrlst;

t_arrlst	*init_arrlst(int capacity);

void		append_arrlst(t_arrlst *list, void *data);

void		free_arrlst(t_arrlst *list, void (*del)(void *));

int			ft_match(char *s1, char *s2);

int			*int_arrdup(int *src, int size);

char		*skip_to(char **text, char *set);

char		*skip_set(char **text, char *set);

char		*skip_while(char **text, int (*condition)(char));

char		*skip_len(char **text, int size);

#endif
