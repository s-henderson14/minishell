/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/10 13:27:16 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 14:49:20 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dst_y;
	const char	*src_y;

	dst_y = dst;
	src_y = src;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		dst_y[i] = src_y[i];
		i++;
	}
	return (dst);
}
/*
int main()
{
	size_t n = 3;
	char dst[10] = "";
	const char src[] = "lemonade";

	printf("%s\n", ft_memcpy(dst, src, n));
	char ds[10] = "";
	printf("%s\n", memcpy(ds, src, n));
}
*/
