/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 11:57:08 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 15:23:11 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ch;
	unsigned int	n;

	ch = b;
	n = 0;
	while (n < len)
	{	
		*ch = (unsigned char) c;
		ch++;
		len--;
	}
	return (b);
}
/*
int main()
{
	size_t  len = 9;
    char b[10] = "";
	int c = 'b';

	printf("%s\n", ft_memset(b, c, len));
	printf("%s\n", memset(b, c, len));
		
}
*/
