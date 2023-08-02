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

void	init_command_structure(char **argv, int argc, t_tools *tools)
{	
	char **args;

	args = argv_duplicate_without_program_name(argv, argc); //MALLOCss!
	//printf("%s %s\n", args[0], args[1]);
	tools->command_list = ft_lstnew_command(args);
	//ft_lstadd_back_command(tools->command_list, command); //MALLOCC
}

//TEST 
void choose_builtin(char **argv, t_tools *tools)
{
	t_command *command;

	command = tools->command_list;
	if (argv[1] == NULL)
	{
		printf("Enter a command to run builtin test\n");
		return ;
	}
	if (ft_strsame(command->args[0], "cd") == 1)
		mini_cd(tools, command);
	if (ft_strsame(command->args[0], "pwd") == 1)
		mini_pwd(tools);
	if (ft_strsame(command->args[0], "echo") == 1)
		mini_echo(tools, command);
	if (ft_strsame(command->args[0], "env") == 1)
		mini_env(tools, command);
	else
		return ;
}

// if (ft_strsame(argv[1], "cd") != 1 && ft_strsame(argv[1], "echo") != 1
// 				&& ft_strsame(argv[1], "pwd") != 1 && ft_strsame(argv[1], "env") != 1
// 				&& ft_strsame(argv[1], "exit") != 1 && ft_strsame(argv[1], "export") != 1)
// 				break ;
