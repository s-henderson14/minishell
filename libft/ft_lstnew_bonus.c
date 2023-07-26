/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 16:08:43 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/07 16:08:49 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*nd;

	nd = (t_list *)malloc(sizeof(t_list));
	if (nd == NULL)
		return (NULL);
	nd -> content = content;
	nd -> next = NULL;
	return (nd);
}
