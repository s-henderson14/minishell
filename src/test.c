#include "../include/minishell.h"

/*
**	Creates an example command_list structure to test builtin functions. 
**	typedef struct s_command
**	{
**    	char **args;
**	    t_redirection *redirection;
**	    struct s_command *next;
**	}t_command;
*/
// void malloc_command_list_structure(t_tools *tools)
// {
// 	t_command *temp;
// 	int i;
// 	int number_of_command_element_in_list;

// 	i = 0;
// 	tools->command_list = ft_lstnew_bonus()
// 	temp = tools->command_list;
// 	number_of_command_element_in_list = tools->number_of_pipes + 1;
// 	while (i < number_of_command_element_in_list)
// 	{
// 		tools->command_list = tools->command_list->next;
// 		tools->command_list = malloc(sizeof(t_command));
// 		if (tools->command_list == NULL)
// 			exit (1);
// 		temp = tools->command_list;
// 		i++;
// 	}
// 	temp = NULL;
// }

void	init_command_structure(int argc, char **argv, t_tools *tools)
{
	char **args;

	args = argv_duplicate_without_program_name(argv, argc); //MALLOCss!
	//printf("%s %s\n", args[0], args[1]);
	tools->command_list = ft_lstnew_command(args);
	//ft_lstadd_back_command(tools->command_list, command); //MALLOCC
}

t_command *init_command_list(char *line, t_tools *tools)
{
	t_command *command_list;
	char **split_line;

	command_list = tools->command_list;
	split_line = ft_split(line, ' ');
	//printf("%s\n%s\n", split_line[0], split_line[1]);
	// for (int i = 0; i < 2; i++)
	// {
	// 	printf("%s\n", split_line[i]);
	// }
	command_list = ft_lstnew_command(split_line);
	//printf("%s\n", command_list->args[0]);
	return (command_list);
}

//TEST 
void choose_builtin(t_tools *tools)
{
	t_command *command;

	command = tools->command_list;
	if (ft_strsame(command->args[0], "cd") == 1)
		mini_cd(tools, command);
	if (ft_strsame(command->args[0], "pwd") == 1)
		mini_pwd(tools);
	if (ft_strsame(command->args[0], "echo") == 1)
		mini_echo(tools, command);
	if (ft_strsame(command->args[0], "env") == 1)
		mini_env(tools, command);
	if (ft_strsame(command->args[0], "exit") == 1)
		mini_exit(tools, command);
	if (ft_strsame(command->args[0], "unset") == 1)
		mini_unset(tools, command);
	if (ft_strsame(command->args[0], "export") == 1)
		mini_export(tools, command);
	else
		return ;
}

// if (ft_strsame(argv[1], "cd") != 1 && ft_strsame(argv[1], "echo") != 1
// 				&& ft_strsame(argv[1], "pwd") != 1 && ft_strsame(argv[1], "env") != 1
// 				&& ft_strsame(argv[1], "exit") != 1 && ft_strsame(argv[1], "export") != 1)
// 				break ;
