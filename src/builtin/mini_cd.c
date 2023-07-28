#include "../../include/minishell.h"

//void change_value_of_env_key(char *new_value, char *key, t_env_node *env_list)

void	store_oldpwd(t_tools *tools)
{
	char	
	t_env_node	*env_list;

	env_list = tools->env_list;

}

int mini_cd(t_tools *tools, t_command *command)
{
	char	*target;
	char	*current_pwd;
	t_env_node	*env_list;

	env_list = tools->env_list;
	if (command->args[1] == NULL)
	{
		target = get_value_from_env_arr(env_list); //MALLOC
		//before changing store old pwd value;
		change_value_of_env_key(target, "HOME=", env_list);
	}

}