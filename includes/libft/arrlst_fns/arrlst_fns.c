/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrlst_fns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:09:25 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:21:08 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_arrlst	*init_arrlst(int capacity)
{
	t_arrlst	*arrlst;

	arrlst = malloc(sizeof(t_arrlst));
	if (!arrlst)
		return (NULL);
	arrlst->capacity = capacity;
	arrlst->count = 0;
	arrlst->content = ft_calloc((capacity + 1), sizeof(void *));
	if (!arrlst->content)
		arrlst->capacity = 0;
	return (arrlst);
}

static void	**grow_array(t_arrlst *list, int old_capacity, int new_capacity)
{
	void	**new_array;

	new_array = ft_calloc((new_capacity + 1), sizeof(void *));
	if (!new_array)
		return (NULL);
	ft_memcpy(new_array, list->content, (old_capacity * sizeof(void *)));
	free(list->content);
	return (new_array);
}

void	append_arrlst(t_arrlst *list, void *data)
{
	int	old_capacity;

	if (list->capacity < list->count + 1)
	{
		old_capacity = list->capacity;
		list->capacity = old_capacity * 2;
		list->content = grow_array(list, old_capacity, list->capacity);
		if (!list->content)
			return ;
	}
	list->content[list->count] = data;
	list->count++;
}

void	free_arrlst(t_arrlst *list, void (*del)(void *))
{
	int	i;

	i = 0;
	while (i < list->count)
		del((list->content)[i++]);
	free(list->content);
	free(list);
}
/*
int main(void)
{
	char		*str = "hello my name is Eden";
	char		**split;
	t_arrlst	*list = init_arrlst(3);
	int			i = 0;
	void		**tmp;

	split = ft_split(str, ' ');
	while (split[i])
	{
		append_arrlst(list, (void *)split[i]);
		i++;
	}
	tmp = list->content;
	while (*tmp)
	{
		ft_printf("%s\n", (char *)(*tmp));
		tmp++;
	}
	free_arrlst(list, free);
	free(list);
	free(split);
}
*/