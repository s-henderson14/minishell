#include "../../include/minishell.h"

int check_first_char_dollar(char *string)
{
	if (*string != '$')
		return (0);
	else
		return (1);
}

/*
**	expand_string() handles $? and $ENV_VAR
*/
char *expand_string(char *string, t_tools *tools)
{
	t_env_node	*temp;
	char		*return_val;

	if (ft_strsame(string, "$?") == 1)
	{
		return_val = ft_itoa(glob_exit_status); //MALLOCCC
		return (return_val);
	}
	temp = tools->env_list;
	while (temp != NULL)
	{
		if (ft_strsame(string + 1, temp->key) == 1)
		{
			return_val = get_value_from_env_node(temp->key, tools->env_list); //MALLOCCC
			return (return_val);
		}
		temp = temp->next;
	}
	return (NULL);
}
