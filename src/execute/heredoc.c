#include "../../include/minishell.h"

void check_heredoc(t_command *command)
{
	t_redirection *redirection;

	redirection = command->redirection;
	if (redirection == NULL)
		return ;
	while (redirection != NULL)
	{
		if (redirection->type == LESS_LESS && redirection)
		{
			here_document(redirection);
		}
		redirection = redirection->next;
	}
}

void here_document(t_redirection *redirection)
{
	char *line;
	char *delimiter;
	int fd_pipe[2];

	delimiter = redirection->file_name;
	if (delimiter == NULL)
		error_exit("minishell: syntax error near unexpected token `newline'", 258);
	if (pipe(fd_pipe) == -1)
		error_exit("minishell: syntax error near unexpected token `newline'", 1);
	while (1)
	{
		signal_noninteractive();
		line = readline("> ");
		if (line == NULL)
			break;
		if (ft_strsame(line, delimiter) == 1)
		{
			free(line);
			break ;
		}
		write(fd_pipe[1], line, ft_strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
	}
	protected_dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
//	return (EXIT_SUCCESS);
}