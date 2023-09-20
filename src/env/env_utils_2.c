#include "../../include/minishell.h"

int check_key_exist(char *key, t_env_node *env_list)
{
	while (env_list != NULL)
	{
		if (ft_strsame(key, env_list->key) == 1)
			return (1);
		env_list = env_list->next;
	}
	return (0);
}

void print_value(char *key, t_tools *tools)
{
	t_env_node *env_list;

	env_list = tools->env_list;
	while (env_list != NULL)
	{
		if (ft_strsame(env_list->key, key) == 1)
			printf("%s", env_list->value);
		env_list = env_list->next;
	}
}
