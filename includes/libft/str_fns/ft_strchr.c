/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strchr.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: eamsalem <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/04/14 13:33:11 by eamsalem		  #+#	#+#			 */
/*   Updated: 2024/04/15 11:33:34 by eamsalem		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../libft.h"

// Returns a pointer to the first occurrence of a chr in a str.

const char	*ft_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}
/*
int	main(void)
{
	printf("%p\n", ft_strchr("hello", 'l'));
	printf("%p\n", ft_strchr("hello", 'b'));
	printf("%p\n", ft_strchr("hello", '\0'));
}*/
