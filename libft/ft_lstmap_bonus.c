/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/07 15:43:39 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/07 16:08:22 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*create_nd(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	void	*content;

	content = f(lst->content);
	new_lst = ft_lstnew(content);
	if (new_lst == NULL)
	{
		ft_lstclear(&new_lst, del);
		del(content);
	}
	return (new_lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	t_list	*new_lst;
	void	*content;

	if (!lst)
		return (0);
	new_lst = create_nd(lst, f, del);
	while (lst->next != NULL)
	{
		lst = lst->next;
		content = f(lst->content);
		temp = ft_lstnew(content);
		if (temp == NULL)
		{
			ft_lstclear(&temp, del);
			del(content);
		}
		ft_lstadd_back(&new_lst, temp);
	}
	return (new_lst);
}
