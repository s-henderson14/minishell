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

void free_key_and_value(char *key, char *value)
{
	free(key);
	free(value);
}

// void remove_oldpwd(t_env_node *env_list)
// {
// 	t_env_node *temp;
// 	t_env_node *bacup;

// 	bacup = env_list;
// 	temp = env_list;
// 	while(temp != NULL)
// 	{
// 		if (ft_strsame(temp->key, "OLDPWD") == 1)
// 		{
// 			bacup = temp->next;
// 			env_node_free(temp);
// 			break ;
// 		}
// 		else
// 		{
// 		bacup = temp;
// 		temp = temp->next;
// 		}
// 	}
// }