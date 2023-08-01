#include "../../include/minishell.h"

/*
**	Prints environment variables, doesnt accept extra parameters, gives error
**	If list is empty, doesnt return error
**	Also ignores empty keys, doesnt print them
*/
int mini_env(t_tools *tools, t_command *command)
{
	t_env_node *env_list;

	env_list = tools->env_list;
	if (env_list == NULL)
		return glob_exit_status;
	if (command->args[0] != NULL && command->args[1] != NULL)
	{
		ft_putendl_fd("env:  too many arguments\n", STDERR_FILENO);
		glob_exit_status = 127;
		return (glob_exit_status);
	}
	env_list_print(env_list);
	return (glob_exit_status);
}