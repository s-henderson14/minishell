#include "../../include/minishell.h"

t_command	*ft_lstnew_command(char **dup)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command -> args = dup;
	command->redirection = NULL;
	command -> next = NULL;
	return (command);
}

void	ft_lstadd_back_command(t_command *command_list, t_command *command)
{
	t_command	*temp;

	if (command == NULL)
		return ;
	if (command_list == NULL)
	{	
		command_list = command;
		command->next = NULL;
		return ;
	}
	temp = command_list;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = command;
}