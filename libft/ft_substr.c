/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 15:04:47 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 12:54:46 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{	
	char	*sub;
	size_t	i;
	size_t	s_len;

	s_len = ft_strlen(s);
	i = 0;
	if (!s)
		return (0);
	if (start >= s_len || start < 0 || len <= 0)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	sub = (char *)malloc(len + 1);
	if (!sub)
		return (0);
	while (s[start] != '\0' && i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
/*
int main()
{
    char const *s = "lemonade";
    unsigned int start = 9;
    size_t len = 4;

    printf("%s\n", ft_substr(s, start, len));
}
*/
