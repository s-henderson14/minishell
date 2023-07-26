/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 12:53:37 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 12:54:21 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (0 <= len)
	{
		if (s[len] == (char)c)
		{
			return ((char *)(s + len));
		}
		len--;
	}
	return (NULL);
}
/*
int main()
{
        const char s[10] = "bananalar";
        int c = 'a';
        printf("%s\n", ft_strrchr(s, c));
        printf("%s\n", strrchr(s, c));
}
*/
