t_env_node *init_env_linked_list(char *env)

/*
	Creates a new node for env list, 
	Memory for key and value is already ALLOCATED in get_key_from_env_arr()
	and get_value_from_env_arr()
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
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

//check create_node() AGAIN!!!
char *get_key_from_env_arr(char **env)

//check create_node() AGAIN!!! if value == NULL ???
char *get_value_from_env_arr(char **env)

void change_value_of_key(char *new_value, t_env_node *env_list)