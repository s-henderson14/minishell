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
		exit_code = execute_single_command(tools, command);
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
	int fd_in;
	int fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	command_list = tools->command_list;
	//printf("command args = %s %s \n", command_list->args[0], command_list->args[1]);
	if (tools->number_of_pipes == 0)
	{
		if (is_builtin(command_list) == 1)
		{
			if (redirection(command_list) == 1)
				return ;
			choose_builtin(tools);
		}
		else
		{	
			if (redirection(command_list) == 1)
				return ;
			execute_without_pipe(tools);

		}
	}
	else
	{
		handle_pipes(tools);
		//printf("here pipes need to be execute()\n");
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}
