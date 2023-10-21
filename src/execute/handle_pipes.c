#include "../../include/minishell.h"

void handle_pipes(t_tools *tools)
{
	t_command	*command_list;
	t_command	*temp;
	int fd[2];
	int fd_input;

	command_list = tools->command_list;
	fd_input = dup(STDIN_FILENO); //first command has input from STDIN_FI
	temp = command_list;
	while (temp->next != NULL)
	{
		if (pipe(fd) == -1)
		{
			error_exit("pipe() failed", 1);
		}
		else
		{
			single_execution_in_pipe(tools, temp, fd_input, fd);
		}
		close(fd[1]); //i ll call pipe again for next command
		fd_input = dup(fd[0]);
		temp = temp->next;
	}
	//pipe(fd);
	printf("fd_input in handle %d\n", fd_input);
	last_command_execution(tools, temp, fd_input, fd);
	//get return value;
}

int single_execution_in_pipe(t_tools *tools, t_command *command, int fd_input, int fd[])
{
	pid_t	p1;
	//int		exit_code;

	// redirection(command);
	check_heredoc(command);
	p1 = fork();
	if (p1 == -1)
	{
		//close all fd's
		error_exit("fork() failed", 1);
	}
	else if (p1 == 0)
	{
		close(fd[0]);
		protected_dup2(fd_input, STDIN_FILENO);
		protected_dup2(fd[1], STDOUT_FILENO);
		//close(fd[0]);
		redirection(command);
		if (is_builtin(command) == 1)
			return (choose_builtin(tools));
		execute_single_command(tools, command); // command will change each call
	}
	// else
	// 	wait(NULL);
	return (EXIT_SUCCESS);
}

int last_command_execution(t_tools * tools, t_command *command, int fd_input, int fd[])
{
	pid_t	p1;
	//int		exit_code;
	(void)fd;

	check_heredoc(command);
	p1 = fork();
	if (p1 == -1)
	{
		error_exit("fork() failed", 1);
	}
	else if (p1 == 0)
	{
		printf("fd_input in last_command %d\n", fd_input);
		protected_dup2(fd_input, STDIN_FILENO);
		redirection(command);
		choose_builtin(tools);
		execute_single_command(tools, command);
	}
	//close(fd[0]);
	close(fd_input);
	wait(NULL);
	return (EXIT_SUCCESS);
}