/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tolower.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 12:55:16 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 12:56:06 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if ((c >= 'A') && (c <= 'Z'))
	{
		c += 32;
	}
	return (c);
}
/*
int main()
{
        int c = 'T';
        printf("%c\n", ft_tolower(c));
        printf("%c\n", tolower(c));
}*/
