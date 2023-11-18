#include "../../include/minishell.h"

/*
**	Prints the current working directory
**	For getcwd(), see manual
**	This funtion ignores extra parameters, still prints
*/
int	mini_pwd(t_tools *tools)
{
	char	*cwd;

	(void)tools;
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putendl_fd("pwd: command fails\n", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (EXIT_SUCCESS);
}
