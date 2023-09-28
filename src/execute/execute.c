#include "../../include/minishell.h"

/*
**	is_builtin() checks if given command is a built-in command
*/
int is_builtin(t_command *command)
{
	//printf("BUILTINN");
	return (ft_strsame(command->args[0], "cd") == 1
			|| ft_strsame(command->args[0], "echo") == 1
			|| ft_strsame(command->args[0], "pwd") == 1
			|| ft_strsame(command->args[0], "env") == 1
			|| ft_strsame(command->args[0], "exit") == 1
			|| ft_strsame(command->args[0], "export") == 1
			|| ft_strsame(command->args[0], "unset") == 1);
}

/*
**	simple_command_exec() handles execution of a single command without pipe.
*/
void execute_without_pipe(t_tools *tools)
{
	t_command *command;
	int exit_code;
	pid_t p1;

	command = tools->command_list;
	p1 = fork();
	if (p1 == -1)
		error_exit("fork failed", 1);
	else if (p1 == 0)
	{
		execute_single_command(tools, command);
	}
	else
	{
		waitpid(p1, &exit_code, 0);
		glob_exit_status = exit_code;
	}
}

void execute(t_tools *tools)
{
	t_command *command_list;

	command_list = tools->command_list;
	//printf("command args = %s %s %s\n", command_list->args[0], command_list->args[1], command_list->args[2]);
	if (tools->number_of_pipes == 0)
	{
		if (is_builtin(command_list) == 1)
		{
			redirection(command_list);
			choose_builtin(tools);
		}
		else
		{	
			redirection(command_list);
			execute_without_pipe(tools);
		}
	}
	else
	{
		handle_pipes(tools);
		//printf("here pipes need to be execute()\n");
		return ;
	}
}
