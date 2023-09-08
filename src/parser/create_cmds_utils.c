#include "../include/minishell.h"

void	add_cmd_front(t_command **cmd_lst, t_command *new_cmd)
{
	new_cmd->next = *cmd_lst;
	*cmd_lst = new_cmd;
}

void	add_cmd_back(t_command **cmd_lst, t_command *new_cmd)
{
	t_command	*tmp;

	tmp = *cmd_lst;
	if (*cmd_lst == NULL)
	{	
		add_cmd_front(cmd_lst, new_cmd);
		return ;
	}
  	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
}

int	word_counter(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{	
			i++;
			if (s[i] == c || s[i] == '\0')
				count++;
		}
	}
	return (count);
}