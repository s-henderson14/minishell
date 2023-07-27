/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strsame.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/03 12:29:07 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 12:29:48 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strsame(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
