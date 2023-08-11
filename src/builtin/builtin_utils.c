#include "../../include/minishell.h"

t_command	*ft_lstnew_command(char **dup)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->args = dup;
	if (command->args[1] == NULL)
        command->redirection = NULL;
    else
    	command->redirection = init_redirection(command);
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

int check_arg_digit(char *arg)
{
	if (arg == NULL)
		return (0);
	while (*arg != '\0')
	{
		if (ft_isdigit(*arg) != 1)
			return (0);
		arg++;
	}
	return (1);
}

/*
** 	Searchs equal sign in given string. If finds returns its index position. Else, -1
*/
int find_equal_sign(char *arg)
{
	int i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}