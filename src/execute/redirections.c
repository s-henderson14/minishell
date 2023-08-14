#include "../../include/minishell.h"

void protected_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		error_exit("dup2(): failed", 1);
}

int input_redirection(t_redirection *redirection)
{
	int fd;

	fd = open(redirection->file_name, O_RDONLY, 0644);
	if (fd < 1)
		error_exit("open(): failed", 1);
	protected_dup2(fd, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int output_redirection(t_redirection *redirection)
{
	int fd;

	fd = 0;
	if (redirection->type == GREAT)
	{
		fd = open(redirection->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			error_exit("open(): failed", 1);
	}
	else if (redirection->type == GREAT_GREAT)
	{
		fd = open(redirection->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			error_exit("open(): failed", 1);
	}
	protected_dup2(fd, STDOUT_FILENO);
	return (EXIT_SUCCESS);
}

int redirection(t_command *command)
{
	t_redirection *redirection;

	redirection = command->redirection;
	while (redirection != NULL)
	{
		if (redirection->type == GREAT || redirection->type == GREAT_GREAT)
		{
			if (output_redirection(redirection) == 1)
				return (EXIT_FAILURE);
		}
		else if (redirection->type == LESS)
		{
			if (input_redirection(redirection) == 1)
				return (EXIT_FAILURE);
		}
		else if (redirection->type == LESS_LESS)
		{
			if (here_document(redirection) == 1)
				return (EXIT_FAILURE);
		}
		redirection = redirection->next;
	}
	return (EXIT_SUCCESS);
}