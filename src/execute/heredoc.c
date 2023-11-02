#include "../../include/minishell.h"

// static char	*tmp_filename(int i)
// {
// 	char	*file_no;
// 	char	*filename;

// 	file_no = ft_itoa(i);
// 	filename = ft_strjoin("src/.temp", file_no);
// 	free(file_no);
// 	return (filename);
// }


// void	here_document(char *delimiter, char *temp_file)
// {
// 	int		fd_temp;
// 	char	*line;

// 	fd_temp = open(temp_file, O_CREAT | O_RDWR | O_TRUNC, 0000644);
// 	if (fd_temp < 0)
// 	{
// 		unlink(temp_file);
// 		error_exit("open() heredoc", 1);
// 	}
// 	while (1)
// 	{
// 		//signal(SIGINT, signal_heredoc);
// 		signal_noninteractive();
// 		line = readline("> ");
// 		if (line == NULL)
// 			break ;
// 		if (ft_strsame(delimiter, line) == 1)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		write(fd_temp, line, ft_strlen(line));
// 		write(fd_temp, "\n", 1);
// 		free(line);
// 	}
// 	free(delimiter);
// 	// if (line)
// 	// 	free(line);
// //	close(fd_temp);
// }

// void	check_heredoc(t_command *command)
// {
// 	static int	i;
// 	char	*temp_file;
// 	char	*delimiter;

// 	t_redirection *redirection;

// 	redirection = command->redirection;
// 	if (redirection == NULL)
// 		return ;
// 	while (redirection != NULL)
// 	{
// 		if (redirection->type == LESS_LESS && redirection)
// 		{
// 			delimiter = redirection->file_name;
// 			temp_file = tmp_filename(i);
// 			i++;
// 			here_document(delimiter, temp_file);
// 		}
// 		redirection = redirection->next;
// 	}
// }


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
		//	printf("file = %s\n", redirection->file_name);
			here_document(command, redirection);
		}
		redirection = redirection->next;
	}
}

void here_document(t_command *command, t_redirection *redirection)
{
	char *line;
	char *delimiter;
	int fd_pipe[2];
	(void)command;

	delimiter = redirection->file_name;
	//printf("LELLO\n");
	if (delimiter == NULL)
		error_exit("minishell: syntax error near unexpected token `newline'", 258);
	if (pipe(fd_pipe) == -1)
		error_exit("minishell: syntax error near unexpected token `newline'", 1);
	//line = readline("> ");
	//while (line != NULL && ft_strsame(line, delimiter) != 1)
	while (1)
	{
		signal_noninteractive();
		line = readline("> ");
		if (line == NULL)
		{
			//printf("LINE NULL\n");
			break;
		}
		if (ft_strsame(line, delimiter) == 1)
		{
			free(line);
			break ;
		}
		write(fd_pipe[1], line, ft_strlen(line));
		write(fd_pipe[1], "\n", 1);
		free(line);
		//line = readline("> ");
	}
	// if (line)
	// 	free(line);
	//if (command->redirection->next == NULL)
	protected_dup2(fd_pipe[0], STDIN_FILENO);
	//dup2(fd_pipe[0], STDIN_FILENO);
	close(fd_pipe[1]);
//	return (EXIT_SUCCESS);
}