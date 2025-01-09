/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 13:37:18 by eamsalem          #+#    #+#             */
/*   Updated: 2024/09/26 09:23:51 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Used a branchless programming technique which improves efficiency to
// help me learn this style

int	ft_toupper(int c)
{
	return (c -= 32 * (c >= 'a' && c <= 'z'));
}

/*
#include <stdio.h>

int	main(void)
{
	printf("%c\n", ft_toupper('a'));
	printf("%c\n", ft_toupper('A'));

}*/
