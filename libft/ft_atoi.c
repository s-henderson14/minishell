/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/12 12:59:08 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/03 15:00:26 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	is_space(char c)
{
	return (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v');
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long int	n;
	int					sign;

	i = 0;
	n = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	if (n > LONG_MAX && sign == -1)
		return (0);
	return ((int)(n * sign));
}
/*
int main()
{
	const char s[] = "2147483649";
	printf("%d\n", ft_atoi(s));
	printf("%d\n", atoi(s));
}
*/
