/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isascii.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/08 15:31:40 by gozturk       #+#    #+#                 */
/*   Updated: 2022/10/17 14:27:29 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_isascii(int c)
{
	return ((c >= 0) && (c <= 127));
}
/*
int main ()
{
    int  c = 129;
    printf("%d\n", ft_isascii(c));
    printf("%d\n", isascii(c));
}
*/
