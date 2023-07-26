/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/14 13:35:03 by gozturk       #+#    #+#                 */
/*   Updated: 2022/10/17 14:20:58 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	len;

	len = ft_strlen(s1) + 1;
	dst = (char *)malloc(sizeof(char) * (len));
	if (dst)
		ft_memcpy(dst, s1, len);
	return (dst);
}
/*
int main()
{
	const char s1[13] = "lemonade";

	printf("%s\n", ft_strdup(s1));
	printf("%s\n", strdup(s1));
}
*/
