#include "../../include/minishell.h"

void mini_env(t_tools *tools, t_command *command)
{
	t_env_node *env_list;

	env_list = tools->env_list;
	if (env_list == NULL)
		return ;
	if (command->args[0] != NULL && command->args[1] != NULL)
	{
		ft_putendl_fd("env:  too many arguments\n", STDOUT_ERROR);
		glob_exit_status = 1;
		return ;
	}
	env_list_print(env_list);
}