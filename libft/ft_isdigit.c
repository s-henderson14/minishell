/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 15:40:09 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 15:20:39 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	int	is_digit;

	is_digit = ((c >= '0') && (c <= '9'));
	return (is_digit);
}
/*
int main()
{
	int c; 
    c =	'3';
	printf("%d\n", ft_isdigit(c));
	printf("%d\n", isdigit(c));
}
*/
