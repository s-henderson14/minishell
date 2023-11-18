#include "../../include/minishell.h"

t_env_node	*split_arg_and_create_node(char *arg)
{
	t_env_node	*new_node;
	char		*key;
	char		*value;

	key = get_key_from_env_arr(arg);
	value = get_value_from_env_arr(arg);
	new_node = env_node_create(key, value);
	if (new_node == NULL)
		return (NULL);
	return (new_node);
}

void	print_env_for_export(t_env_node *env_list)
{
	t_env_node	*temp;

	temp = NULL;
	if (env_list == NULL)
		return ;
	temp = env_list;
	while (temp != NULL)
	{
		printf("declare -x ");
		printf("%s=\"%s\"\n", temp->key, temp->value);
		temp = temp->next;
	}
}

int	mini_export(t_tools *tools, t_command *command)
{
	t_env_node	*env_list;
	t_env_node	*new_node;

	new_node = NULL;
	env_list = tools->env_list;
	if (env_list != NULL && command->args[0]
		!= NULL && command->args[1] == NULL)
	{
		print_env_for_export(env_list);
		return (EXIT_SUCCESS);
	}
	else if (command->args[0] != NULL
		&& check_arg_digit(command->args[1]) == 1)
	{
		error_exit("bash: export: no valid identifier", 1);
		return (EXIT_FAILURE);
	}
	else if (env_list != NULL && check_arg_digit(command->args[1]) == 0
		&& find_equal_sign(command->args[1]) != -1)
	{
		new_node = split_arg_and_create_node(command->args[1]);
		env_node_add_back(new_node, env_list);
	}
	return (EXIT_FAILURE);
}
