#include "../include/minishell.h"

int count_tokens(t_token **tkn_list)
{
    int		i;
    t_token	*tmp;

    i = 0;
    tmp = *tkn_list;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}