#include "../../include/minishell.h"

void check_heredoc(t_command *command)
{
	t_redirection *redirection;

	redirection = command->redirection;
	if (redirection == NULL)
		return ;
	while (redirection != NULL)
	{
		if (redirection->type == LESS_LESS)
		{
			if (here_document(redirection) == 1)
				return ;
		}
		redirection = redirection->next;
	}
}

int here_document(t_redirection *redirection)
{
	char *line;
	char *delimiter;
	int fd_pipe[2];

	delimiter = redirection->file_name;
	if (delimiter == NULL)
	{
		error_exit("minishell: syntax error near unexpected token `newline'", 258);
	}
	if (pipe(fd_pipe) == -1)
		return (EXIT_FAILURE);
	while (1)
	{
		line = readline("> ");
		if (ft_strsame(line, delimiter) == 1)
		{
			free(line);
			break ;
		}
		if (line[0] != '\0')
		{
			write(fd_pipe[1], line, ft_strlen(line));
			write(fd_pipe[1], "\n", 1);
		}
		free(line);
	}
	protected_dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	return (EXIT_SUCCESS);
}