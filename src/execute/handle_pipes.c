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
		check_heredoc(temp);
		if (pipe(fd) == -1)
		{
			error_exit("pipe() failed", 1);
		}
		else
		{
			single_execution_in_pipe(tools, temp, &fd_input, fd);
		}
		close(fd[1]); //i ll call pipe again for next command
		fd_input = dup(fd[0]);
		close(fd[0]);
		temp = temp->next;
	}
	//printf("fd_input in handle %d\n", fd_input);
	latest_status(last_command_execution(tools, temp, &fd_input, fd));
}

void single_execution_in_pipe(t_tools *tools, t_command *command, int *fd_input, int fd[])
{
	pid_t	p1;
	//int		exit_code;

	p1 = fork();
	if (p1 == -1)
	{
		//close all fd's
		error_exit("fork() failed", 1);
	}
	else if (p1 == 0)
	{
		child_exec_in_pipe(tools, command, fd_input, fd);
	}
}

void child_exec_in_pipe(t_tools * tools, t_command *command, int *fd_input, int fd[])
{
	close(fd[0]);
	protected_dup2(*fd_input, STDIN_FILENO);
	protected_dup2(fd[1], STDOUT_FILENO);//FIRST EXEC, fd[1] == ????
//	printf("STDOUT 2= %d\n", STDOUT_FILENO);
	if (command->redirection)
		redirection(command);
//	printf("After REDIRECTOIN (2) STDOUT = %d\n", STDOUT_FILENO);
	if (is_builtin(command) == 1)
		exit(exec_builtin(tools));
	//printf("B\n");
	call_execve(tools, command); // command will change each call
}

int last_command_execution(t_tools * tools, t_command *command, int *fd_input, int fd[])
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
	//	printf("fd_input in last_command %d\n", *fd_input);
		protected_dup2(*fd_input, STDIN_FILENO);
		if (command->redirection)
			redirection(command);
	//	exec_builtin(tools);
		if (is_builtin(command) == 1)
		{
			exit(exec_builtin(tools));
		}
		call_execve(tools, command);
	}
	close(fd[0]);
	close(*fd_input);
	//waitpid(p1, NULL, 0);
	return (p1);
}

/*
	WIFEXITED() Returns a nonzero value if the child terminated normally
	WIFSIGNALED() Returns a nonzero value if the child process terminated
				because it received a signal that was not handled.
*/
int	latest_status(pid_t pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 0)
		g_sig = WEXITSTATUS(status);
	if (WIFSIGNALED(status) != 0)
		g_sig = 128 + status;
	return (g_sig);
}