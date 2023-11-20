#include "../../include/minishell.h"

void	add_token_front(t_token **tkn_lst, t_token *new_tkn)
{
	new_tkn->next = *tkn_lst;
	*tkn_lst = new_tkn;
}

void	add_token_back(t_token **tkn_lst, t_token *new_tkn)
{
	t_token	*tmp;

	tmp = *tkn_lst;
	if (*tkn_lst == NULL)
	{	
		add_token_front(tkn_lst, new_tkn);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_tkn;
}

int count_tokens(t_token **tkn_list)
{
    int		i;
    t_token	*tmp;

    i = 0;
    tmp = *tkn_list;
	while (tmp != NULL)
	{	
		if (tmp->type == 1)
			break;
		if(tmp->type > 2 && tmp->next->type == 2)
			tmp = tmp->next;
		else if (tmp->type == 2)
			i++;
		tmp = tmp->next;
	}
	return (i);
}