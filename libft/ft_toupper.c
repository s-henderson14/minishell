/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_toupper.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 14:44:54 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 14:45:34 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if ((c >= 'a') && (c <= 'z'))
	{
		c -= 32;
	}
	return (c);
}
/*
int main()
{
	int c = '8';
        printf("%c\n", ft_toupper(c));
        printf("%c\n", toupper(c));
}
*/
