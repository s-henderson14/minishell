/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   first_shot.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/06 13:10:06 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 15:20:24 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/*
int main()
{
	int c = 75;
	printf("%d\n", ft_isalpha(c));
	printf("%d\n", isalpha(c));
}
*/
