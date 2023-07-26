/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 12:29:07 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 12:29:48 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	first_s;
	unsigned char	second_s;

	i = 0;
	while (i < n)
	{
		first_s = (unsigned char) s1[i];
		second_s = (unsigned char) s2[i];
		if (first_s != second_s)
		{
			return (first_s - second_s);
		}
		else if (first_s == '\0' && second_s == '\0')
		{
			return (0);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	const char s1[] = "lemonade";
	const char s2[] = "ba";
	size_t n = 3;
	printf("%d\n", ft_strncmp(s1, s2, n));
	printf("%d\n", strncmp(s1, s2, n));
}*/
