#include "../../include/minishell.h"

int error_exit(char *s)
{
	glob_exit_status = 1;
	if (s == NULL)
		return (glob_exit_status);
	ft_putstr_fd(s, STDERR_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (glob_exit_status);
}

char *protect(char *arg)
{
	if (arg == NULL)
	{
		perror("Error"); // so that the error message based on errno will be printed
		glob_exit_status = 1;
		exit(1);
	}
	return (arg);
}

t_command	*ft_lstnew_command(void *content)
{
	t_command	*command;

	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command -> content = content;
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
