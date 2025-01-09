/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strunion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 14:14:32 by eamsalem          #+#    #+#             */
/*   Updated: 2025/01/06 14:15:02 by eamsalem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// This function unites an array of strings into a single, continous string

int	get_len(char **str_arr)
{
	int	i;
	int	tot_len;

	i = 0;
	tot_len = 0;
	while (str_arr[i])
		tot_len += ft_strlen(str_arr[i++]);
	return (tot_len);
}

char	*ft_strunion(char **str_arr)
{
	int		i;
	int		tot_len;
	char	*str;

	tot_len = get_len(str_arr);
	str = malloc(sizeof(char) * (tot_len + 1));
	if (!str)
		return (NULL);
	i = 0;
	str[0] = '\0';
	while (str_arr[i])
		ft_strlcat(str, str_arr[i++], tot_len + 1);
	return (str);
}
/*
int main(void)
{
	printf("%s\n", ft_strunion(ft_split("hello my name is eden", ' ')));

}
*/