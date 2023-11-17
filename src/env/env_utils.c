#include "../../include/minishell.h"

/*
**	It will used in builtin funtions and to debug environment list
*/
void env_list_print(t_env_node *env_list)
{
	while (env_list != NULL)
	{
		if (env_list->value != NULL)
			printf("%s = %s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

/*
**	It gives size of environment list
*/
int env_list_size(t_env_node *env_list)
{
	int size;

	size = 0;
	while (env_list != NULL)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}


/*
** It returns size of env string array
*/
int env_str_arr_size(char **env)
{
	int i;

	i = 0;
	while (env[i] != NULL)
	{
		i++;
	}
	return (i);
}

/*
**	Adds given new node to the end of the env list
*/
void env_node_add_back(t_env_node *new_node, t_env_node *env_list)
{
	t_env_node *temp;

	if (new_node == NULL)
	{
		return ;
	}
	if (env_list == NULL)
	{
		env_list = new_node;
		new_node->next = NULL;
		return ;
	}
	temp = env_list;
	while (temp->next != NULL)
	{
		temp = temp->next;
	}
	temp->next = new_node;
}

/*
**	Frees the single node, by using if statement it protects the node from double free
*/
void env_node_free(t_env_node *node)
{
	if (node == NULL)
	{
		printf("Node is already free\n");
		return ;
	}
	else
	{
		free(node->key);
		free(node->value);
		free(node);
		node = NULL;
	}
}






