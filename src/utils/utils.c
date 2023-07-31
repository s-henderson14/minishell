#include "../../include/minishell.h"

int error_exit(char *s)
{
	glob_exit_status = 1;
	if (s == NULL)
		return (glob_exit_status);
	ft_putstr_fd(s, STDOUT_ERROR);
	write(fd, "\n", 1);
	return (glob_exit_status);
}