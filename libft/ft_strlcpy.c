/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 14:53:39 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 14:57:44 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize <= src_len + 1)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		return (src_len);
	}
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}
/*
int main ()
{
    char dst[15] = "ban";
    const char src[] = "l";
    size_t  dstsize = 0;

    printf("%lu\n", ft_strlcpy(dst, src, dstsize));
    printf("%s\n", dst);
    char ds[15] = "ban";
    printf("%lu\n", strlcpy(ds, src, dstsize));
    printf("%s\n", ds);
}
*/
