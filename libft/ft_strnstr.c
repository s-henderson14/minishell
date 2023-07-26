/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/25 16:36:34 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 12:53:03 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	len_n;

	len_n = ft_strlen(needle);
	i = 0;
	if (len_n == 0)
		return ((char *)(haystack));
	if (ft_strlen(haystack) < len_n)
		return (0);
	while (i < len && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, len_n) == 0)
			{
				if (i + len_n > len)
				{	
					return (0);
				}
				return ((char *)(haystack + i));
			}
		}
		i++;
	}
	return (0);
}
/*
int main()
{
	const char haystack[] = "lemonade";
	const char needle[] = "ona";
	size_t len = 5;
	printf("%s\n", ft_strnstr(haystack, needle, len));
	printf("%s\n", strnstr(haystack, needle, len));
}
*/
