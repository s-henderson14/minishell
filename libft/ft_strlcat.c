/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/19 11:19:46 by gozturk       #+#    #+#                 */
/*   Updated: 2022/10/27 17:49:54 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	j = dst_len;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	if (dstsize > dst_len)
	{
		while (src[i] && i < (dstsize - dst_len - 1))
		{
			dst[j] = src[i];
			i++;
			j++;
		}
		dst[j] = '\0';
		return (dst_len + src_len);
	}
	return (0);
}
/*
int main ()
{
    char dst1[15] = "rrrrrrrrrrrrrrr";
    char dst2[15] = "mrlemonadecaker";
    const char src[] = "lorem ipsum dolor sit amet";
    size_t    dstsize = 5;

    printf("me=%lu\n", ft_strlcat(dst1, src, dstsize));
    printf("me=%s\n", dst1);
    printf("fn=%lu\n", strlcat(dst2, src, dstsize));
    printf("fn=%s\n", dst2);
}
*/
