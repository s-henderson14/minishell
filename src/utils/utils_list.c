#include "../../include/minishell.h"

// t_command	*ft_lstnew_command(char **dup, t_tools *tools)
// {
// 	t_command	*command;

// 	command = (t_command *)malloc(sizeof(t_command));
// 	if (command == NULL)
// 		return (NULL);
// 	command->args = array_dup(dup); //MALLOC
// 	if (command->args == NULL)
// 		return NULL;
//     command->redirection = init_redirection(command);
// 	command -> next = NULL;
// 	return (command);
// }

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


/*
**	Initiates command_list according to pipe existance.
**	 If there is no pipe found, single command node is returned as command_list
**	otherwise everthing until "|" is copied to command->args in a while loop
**	TEST PURPOSE
*/
t_command	*ft_lstnew_command(char **dup, t_tools *tools)
{
	t_command	*command;
	char **temp_args;
	int i;
	int number_of_commands_total;
	static int *pipe_index_position;

	i = 0;
	number_of_commands_total = count_args(dup);
//	printf("commands = %d\n", number_of_commands_total);
	temp_args = array_dup(dup);
	command = (t_command *)malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	tools->command_list = command;
	if (count_pipes(temp_args) == 0)
	{
		command = init_single_command(tools, temp_args);
		return (command);
	}
	//printf("1i = %d\n", i);
	pipe_index_position = malloc(sizeof(int));
	if (pipe_index_position == NULL)
		return (NULL);
//	printf("malloced pipe = %d\n", *pipe_index_position);
	while (temp_args[i] != NULL && i < number_of_commands_total)
	{
	//	printf("1pipe = %d\n", *pipe_index_position);
	//	printf("%s %s %s %s %s\n", temp_args[0], temp_args[1], temp_args[2], temp_args[3], temp_args[4]);
		*pipe_index_position = i;
		//printf("1pipe = %d\n", *pipe_index_position);
		command->args = copy_content_until_pipe(temp_args, pipe_index_position); //MALLOC
		i = *pipe_index_position;
	//	printf("%s\n%s\ni = %d\n", command->args[0], command->args[1], i);  
		if (command->args == NULL)
			return (NULL);
	//	printf("2pipe = %d\n", *pipe_index_position);
		command->redirection = init_redirection(command);
		//printf("temp = %s\n", temp_args[i]);
		if (temp_args[i] != NULL && ft_strsame(temp_args[i], "|") == 1)
		{
			command->next = (t_command *)malloc(sizeof(t_command));
			if (command->next == NULL)
				return (NULL);
		//	printf("temp = %s\n", temp_args[i]);
			command = command->next;
		}
		i++;
	}
	command->next = NULL;
	command = tools->command_list;
	return (command);
}

t_command *init_single_command(t_tools *tools, char **temp_args)
{
	t_command *command;

	command = tools->command_list;
	command->args = temp_args; //MALLOC
	if (command->args == NULL)
		return NULL;
	command->redirection = init_redirection(command);
	command->next = NULL;
	return (command);
}
// void create_command_list(t_command *command_list, t_command *command)
// {
// 	t_command	*command;
// 	char **temp_args;
// 	static int i;
// 	int number_of_command_nodes;

// 	i = 0;
// 	temp_args = array_dup(dup);
// 	number_of_command_nodes = count_pipes(temp_args) + 1;
// 	command = (t_command *)malloc(sizeof(t_command));
// 	if (command == NULL)
// 		return (NULL);
// 	tools->command_list = command;
// 	while (temp_args[i] != NULL)
// 	{
// 		command->args = copy_content_until_pipe(temp_args, i); //MALLOC
// 		if (command->args == NULL)
// 			return (NULL);
// 		command->redirection = init_redirection(command);
// 		if (ft_strsame(temp->args[i], "|") == 1)
// 		{
// 			i++;
// 			command->next = (t_command *)malloc(sizeof(t_command));
// 			if (command->next == NULL)
// 				return (NULL);
// 			command = command->next;
// 		}
// 	}
// 	command = tools->command_list;
// 	return (command);
// }