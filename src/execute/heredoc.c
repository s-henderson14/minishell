#include "../../include/minishell.h"

int here_document(t_redirection *redirection)
{
	char *line;
	char *delimiter;
	int fd_pipe[2];

	delimiter = redirection->file_name;
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
		}
	}
	protected_dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
	return (EXIT_SUCCESS);
}