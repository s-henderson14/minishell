#include "../../include/minishell.h"

/*
**	Creates a linked list from environment variables array (char **env)
**	An example node of env_linked_list is:
**	typedef struct s_env_node
**	{
**	    struct s_env_node    *next;
**	    char            *key;
**	    char            *value;
**	}   t_env_node;
*/
t_env_node *init_env_linked_list(char **env)
{
	t_env_node	*env_list;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		key = get_key_from_env_arr(env[i]); //MALLOC
		value = get_value_from_env_arr(env[i]); //MALLOC
		if (env_list == NULL)
		{
			env_list = env_node_create(key, value);
			if (env_list == NULL)
				return NULL;
		}
		if (env_list != NULL)
			env_node_add_back(env_node_create(key, value), env_list);
		free(key);
		free(value);
		i++;
	}
	return (env_list);
}

/*
**	Creates a new node for env list,
**	Memory for key is already ALLOCATED in get_key_from_env_arr()
*/
t_env_node *env_node_create(char *key, char *value)
{
	t_env_node *new_node;
	if (key == NULL)
	{
		free(value);
		return (NULL);
	}
	new_node = (t_env_node *)malloc(sizeof(t_env_node));
	if (new_node == NULL)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (value != NULL)
		new_node->value = ft_strdup(value);
	else
		new_node->value = NULL; // not sure
	new_node->next = NULL;
	return (new_node);
}

//check create_node() AGAIN!!!
/*
**	param 'char *env_str' --> "KEY=VALUE" single string in env array
**	This funtion extracts key from "KEY=VALUE" single string in env array
*/
char *get_key_from_env_arr(char *env_str)
{
	char *key;
	int i;
	int start;
	int len_key;

	start = 0;
	i = 0;
	while (env_str[i] != '\0')
	{
		if (env_str[i] == '=')
		{
			len_key = i;
			key = ft_substr(env_str, start, len_key); //MALLOCcc
			return (key);
		}
		i++;
	}
	return (NULL);
}

//check create_node() AGAIN!!! if value == NULL ???
//remove strchr()!!!!-->needs malloced str
char *get_value_from_env_arr(char *env_str)
{
	char	*value;
	int i;
	int len_env_str;
	int start;
	int len_value;

	i = 0;
	len_env_str = ft_strlen(env_str);
	while (env_str[i] != '\0' && env_str[i] != '=')
	{
		i++;
	}
	start = i + 1;
	len_value = len_env_str - i - 1;
	value = ft_substr(env_str, start, len_value); //MALLOCCC
	if (value == NULL)
		return NULL;
	return value;
	/*value = ft_strchr(env_str, '=') + 1;
	if (value == NULL)
		return NULL;
	return (value);*/
}

/*
**	Replaces the old_value of a key with the new_value in env_node.
*/
void change_value_of_env_key(char *new_value, char *key, t_env_node *env_list)
{
	while (env_list != NULL)
	{
		if (ft_strsame(env_list->key, key) == 1)
		{
			free(env_list->value);
			env_list->value = ft_strdup(new_value); //MALLOC!!!!!
			return ;
		}
		env_list = env_list->next;
	}
}





