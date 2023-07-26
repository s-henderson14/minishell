/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 17:11:38 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 15:22:38 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	d = dst;
	s = src;
	if (!d && !s)
		return (0);
	if (d < s)
		ft_memcpy(d, s, len);
	else if (d > s)
	{
		while (len)
		{
			d[len - 1] = s[len - 1];
			len--;
		}
	}	
	return (dst);
}
/*
int main()
{
    size_t n = 2;
    char dst[18] = "";
    char src[] = "na";

    printf("%s\n", ft_memmove(dst, src, n));
    printf("%s\n", memmove(dst, src, n));
}
*/
