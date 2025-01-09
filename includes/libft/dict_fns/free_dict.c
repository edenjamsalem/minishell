/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_dict.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 11:39:16 by eamsalem          #+#    #+#             */
/*   Updated: 2024/11/14 11:19:25 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// This function free a single dict node

void	free_dict(t_dict *dict)
{
	free(dict->key);
	free(dict->value);
	free(dict);
}
