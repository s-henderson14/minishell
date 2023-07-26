/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 17:42:12 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 15:22:12 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*first;
	const unsigned char	*second;

	first = s1;
	second = s2;
	i = 0;
	while (i < n)
	{
		if (first[i] != second[i])
		{
			return (first[i] - second[i]);
		}
		i++;
	}
	return (0);
}
/*
int main()
{
    size_t n = 3;
    const unsigned char s1[] = "";
    const unsigned char s2[] = "";

    printf("%d\n", ft_memcmp(s1, s2, n));
    printf("%d\n", memcmp(s1, s2, n));
}
*/
