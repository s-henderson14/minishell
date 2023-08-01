#include "../../include/minishell.h"

/*
**	Prints the current working directory
**	For getcwd(), see manual
**	This funtion ignores extra parameters, still prints
*/
int mini_pwd(t_tools *tools)
{
	char	*cwd;

	(void)tools;
	cwd = getcwd(NULL, 0); //if this one fails, do i have to check value of PWDin env_list?
	if (cwd == NULL)
	{
		ft_putendl_fd("pwd: command fails\n", STDERR_FILENO); //we have a func for the errs
		glob_exit_status = 1;
		return (glob_exit_status);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (glob_exit_status);
}