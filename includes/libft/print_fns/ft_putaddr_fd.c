/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:04:50 by user              #+#    #+#             */
/*   Updated: 2025/01/06 14:12:41 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putaddr_fd(int fd, void *ptr)
{
	if (!ptr)
		return (ft_putstr_fd(fd, "(nil)"));
	write(fd, "0x", 2);
	return (ft_putuslong_base_fd(fd, (unsigned long)ptr, HEX) + 2);
}
