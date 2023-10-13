#include "../../include/minishell.h"

void protected_dup2(int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		error_exit("dup2(): failed", 1);
	close (old_fd);
}

int input_redirection(t_redirection *redirection)
{
	int fd;

	printf("input_filename = %s\n", redirection->file_name); // Changed from %d to %s and tynpe to filename

	fd = open(redirection->file_name, O_RDONLY, 0644);
	if (fd < 1)
	{
		error_exit("open(): failed", 1);
		return (1);
	}
	protected_dup2(fd, STDIN_FILENO);
	return (EXIT_SUCCESS);
}

int output_redirection(t_redirection *redirection)
{
	int fd;

	// fd = 0;
	printf("output_filename = %s\n", redirection->file_name);//Changed from %d to %s and tpe to filename
	if (redirection->type == GREAT)
	{
		//printf("A\n");
		fd = open(redirection->file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fd < 0)
			return (error_exit("open(): failed", 1));
		protected_dup2(fd, STDOUT_FILENO);
	}
	else if (redirection->type == GREAT_GREAT)
	{
			//printf("B\n");

		fd = open(redirection->file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fd < 0)
			return (error_exit("open(): failed", 1));
		protected_dup2(fd, STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}

int redirection(t_command *command)
{
	t_redirection *redirection;

	redirection = command->redirection; // added * for access to array of redir structs
//	printf("filename = %s\n", redirection->file_name);
	while (redirection != NULL)
	{
		printf("redirection name=%s \t redirection_type=%d\n", redirection->file_name, redirection->type);
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