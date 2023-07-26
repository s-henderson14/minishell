/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/13 15:19:42 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 15:43:04 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
/*
int main()
{
	size_t  n = 9;
    char *s = "";

	printf("%s\n", ft_bzero(s, n));
	printf("%s\n", bzero(s, n));
}
*/
