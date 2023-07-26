/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/18 14:01:56 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/04 17:17:28 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *ptr;
        size_t     i;
        size_t     j;

        i = 0;
        j = 0;
        ptr = malloc(sizeof(char) * (ft_strlen(s1) +ft_strlen(s2) + 1));
        if (!ptr)
                return NULL;
        while (ft_strlen(s1) > i && s1[i] != '\0')
        {
                ptr[i] = s1[i];
                i++;
        }
        while (s2[j] != '\0')
        {
                ptr[i] = s2[j];
                i++;
                j++;
        }
        ptr[i] = '\0';
        return (ptr);
}

/*
int main()
{
	char const s1[] = "lemonade";
	char const s2[] = "banana";

	printf("%s\n", ft_strjoin(s1, s2));
}
*/
