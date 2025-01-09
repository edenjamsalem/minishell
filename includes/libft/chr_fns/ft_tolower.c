/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:12:54 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:23:48 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Used a branchless programming technique which improves efficiency to
// help me learn this style

int	ft_tolower(int c)
{
	return (c += 32 * (c >= 'A' && c <= 'Z'));
}
/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_tolower('a'));
	printf("%c\n", ft_tolower('A'));

}*/
