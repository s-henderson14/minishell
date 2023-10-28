#include "../../include/minishell.h"

int exec_builtin(t_tools *tools)
{
	t_command *command;

	command = tools->command_list;
	if (ft_strsame(command->args[0], "cd") == 1)
	{
		return(mini_cd(tools, command));
	}
	if (ft_strsame(command->args[0], "pwd") == 1)
		return(mini_pwd(tools));
	if (ft_strsame(command->args[0], "echo") == 1)
		return(mini_echo(tools, command));
	if (ft_strsame(command->args[0], "env") == 1)
		return(mini_env(tools, command));
	if (ft_strsame(command->args[0], "exit") == 1)
		return(mini_exit(tools, command));
	if (ft_strsame(command->args[0], "unset") == 1)
		return(mini_unset(tools, command));
	if (ft_strsame(command->args[0], "export") == 1)
		return(mini_export(tools, command));
	else
		return (EXIT_FAILURE);
}

void simple_command_no_pipe(t_tools *tools, t_command *command_list)
{
	check_heredoc(command_list);
	if (is_builtin(command_list) == 1)
	{
		if (redirection(command_list) == 1)
			return ;
		g_sig = exec_builtin(tools);
	}
	else
	{
		if (redirection(command_list) == 1)
			return ;
		execute_without_pipe(tools);
	}
}

/*
**	simple_command_exec() handles execution of a single command without pipe.
*/
void execute_without_pipe(t_tools *tools)
{
	t_command *command;
	pid_t p1;

	command = tools->command_list;
	p1 = fork();
	if (p1 == -1)
		error_exit("fork failed", 1);
	else if (p1 == 0)
	{
		call_execve(tools, command);
	}
	else
	{
		latest_status(p1);
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
		simple_command_no_pipe(tools, command_list);
	}
	else
	{
		handle_pipes(tools);
		//printf("here pipes need to be execute()\n");
	}
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}
