#include "../../include/minishell.h"

void find_node_in_list_remove(char *key, t_env_node *env_list)
{
	t_env_node *temp;
	t_env_node *target;

	temp = env_list;
	while (temp != NULL)
	{
		if (ft_strsame(temp->next->key, key) == 1)
		{
			target = temp->next;
			temp->next = temp->next->next;
			env_node_free(target);
			return ;
		}
		temp = temp->next;
	}
}

int mini_unset(t_tools *tools, t_command *command)
{
	t_env_node *env_list;

	env_list = tools->env_list;
	// env_list_print(env_list);
	if (command->args[1] == NULL || check_key_exist(command->args[1], env_list) == 0) //if it doesnt take any argument, "unset"
	{
		return (0);
	}
	if (check_key_exist(command->args[1], env_list) == 1)
	{
		find_node_in_list_remove(command->args[1], env_list);
	}
	//env_list_print(env_list);
	return (EXIT_SUCCESS);
}