#include "../../include/minishell.h"

int here_document(t_redirection *redirection)
{
	char *line;
	char *delimiter;
	int fd[2];

	delimiter = redirection->file_name;
	while (1)
	{
		line = readline("> ");
		if (ft_strsame(line, delimiter) == 1)
			break ;
	}
}