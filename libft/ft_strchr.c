/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 14:53:00 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 14:53:49 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len_s;

	i = 0;
	len_s = ft_strlen(s) + 1;
	while (i < len_s)
	{
		if (s[i] == (char)c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	return (0);
}
/*
int main()
{
        const char s[] = "banana";
        int c = 'n';
        printf("%s\n", ft_strchr(s, c));
        printf("%s\n", strchr(s, c));
}
*/
