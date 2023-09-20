#include "../../include/minishell.h"

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

// void	init_command_structure(int argc, char **argv, t_tools *tools)
// {
// 	char **args;

// 	args = argv_duplicate_without_program_name(argv, argc); //MALLOCss!
// 	//printf("%s %s\n", args[0], args[1]);
// 	printf("%s\n%s\n%s\n%s\n", args[0], args[1], args[2], args[3]);
// 	tools->command_list = ft_lstnew_command(args, tools);
// 	//printf("%s\n%s\n%s\n%s\n", tools->command_list->args[0], tools->command_list->args[1], tools->command_list->args[2], tools->command_list->args[3]);
// 	//ft_lstadd_back_command(tools->command_list, command); //MALLOCC
// }

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
	//printf("%s\n%s\n%s\n%s\n", split_line[0], split_line[1], split_line[2], split_line[3]);
	tools->number_of_pipes = count_pipes(split_line);
//	printf("pipes= %d\n", tools->number_of_pipes);
	command_list = ft_lstnew_command(split_line, tools);
//	printf("%s %s %s %s\n", command_list->args[0], command_list->args[1], command_list->next->args[0], command_list->next->args[1]);//, command_list->next->next->args[0]);
	return (command_list);
}

int count_args_until_pipe(char **args, int i)
{
	int count;
	
	count = 0;
	while (args[i] != NULL)
	{
		if (ft_strsame(args[i], "|") == 1)
			break ;
		count++;
		i++;
	}
	return (count);
}


char **copy_content_until_pipe(char **args, int *pipe_index_position)
{
	int i;
	int j;
	int number_of_commands;
	char **str_arr;

	i = *pipe_index_position;
	j = 0;
	number_of_commands = count_args_until_pipe(args, i);
	//printf("arg number = %d\n", number_of_commands);
	str_arr = (char **)malloc(sizeof(char *) * (number_of_commands + 1));
	//printf("copy_content i = %d\n", i);
	if (str_arr == NULL)
		return (NULL);
	while (args[i] != NULL && j < number_of_commands)
	{
		str_arr[j] = ft_strdup(args[i]); //MALLOC
		i++;
		j++;
		if (args[i] == NULL || ft_strsame(args[i], "|") == 1)
		{
			break ;
		}
	}
	str_arr[j] = NULL;
	*pipe_index_position = i; //next time start copy one index after "|"
//	printf("%s\n%s\ni = %d j = %d\n", str_arr[0], str_arr[1], i, j);
	//printf("pipe index = %d\n", *pipe_index_position);
	return (str_arr);
}

int count_pipes(char **argv)
{
	int count;
	int i;

	i = 0;
	count = 0;
	while (argv[i] != NULL)
	{
		if (ft_strsame(argv[i], "|") == 1)
			count++;
		i++;
	}
	return (count);
}

int count_args(char **args)
{
	int i;

	i = 0;
	while (args[i] != NULL)
	{
		i++;
	}
	return (i);

}

//TEST 

// if (ft_strsame(argv[1], "cd") != 1 && ft_strsame(argv[1], "echo") != 1
// 				&& ft_strsame(argv[1], "pwd") != 1 && ft_strsame(argv[1], "env") != 1
// 				&& ft_strsame(argv[1], "exit") != 1 && ft_strsame(argv[1], "export") != 1)
// 				break ;
