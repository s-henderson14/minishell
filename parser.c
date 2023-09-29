#include "../../include/minishell.h"

// void env_node_add_back(t_env_node *new_node, t_env_node *env_list)
// {
// 	t_env_node *temp;

// 	if (new_node == NULL)
// 	{
// 		return ;
// 	}
// 	if (env_list == NULL)
// 	{
// 		env_list = new_node;
// 		new_node->next = NULL;
// 		return ;
// 	}
// 	temp = env_list;
// 	while (temp->next != NULL)
// 	{
// 		temp = temp->next;
// 	}
// 	temp->next = new_node;
// }

// int env_str_arr_size(char **env)
// {
// 	int i;

// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		i++;
// 	}
// 	return (i);
// }

// char *get_value_from_env_arr(char *env_str)
// {
// 	char	*value;
// 	int i;
// 	int len_env_str;
// 	int start;
// 	int len_value;

// 	i = 0;
// 	len_env_str = ft_strlen(env_str);
// 	while (env_str[i] != '\0' && env_str[i] != '=')
// 	{
// 		i++;
// 	}
// 	start = i + 1;
// 	len_value = len_env_str - i - 1;
// 	value = ft_substr(env_str, start, len_value); //MALLOCCC
// 	if (value == NULL)
// 		return NULL;
// 	return value;
// 	/*value = ft_strchr(env_str, '=') + 1;
// 	if (value == NULL)
// 		return NULL;
// 	return (value);*/
// }


// char *get_key_from_env_arr(char *env_str)
// {
// 	char *key;
// 	int i;
// 	int start;
// 	int len_key;

// 	start = 0;
// 	i = 0;
// 	while (env_str[i] != '\0')
// 	{
// 		if (env_str[i] == '=')
// 		{
// 			len_key = i;
// 			key = ft_substr(env_str, start, len_key); //MALLOCcc
// 			return (key);
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

// t_env_node *env_node_create(char *key, char *value)
// {
// 	t_env_node *new_node;
// 	if (key == NULL)
// 	{
// 		free(value);
// 		return (NULL);
// 	}
// 	new_node = (t_env_node *)malloc(sizeof(t_env_node));
// 	if (new_node == NULL)
// 		return (NULL);
// 	new_node->key = ft_strdup(key);
// 	if (value != NULL)
// 		new_node->value = ft_strdup(value);
// 	else
// 		new_node->value = NULL; // not sure
// 	new_node->next = NULL;
// 	return (new_node);
// }

// t_env_node *init_env_linked_list(char **env)
// {
// 	t_env_node	*env_list;
// 	char	*key;
// 	char	*value;
// 	int		i;

// 	env_list = NULL;
// 	i = 0;
// 	while (env[i] != NULL)
// 	{
// 		key = get_key_from_env_arr(env[i]); //MALLOC
// 		value = get_value_from_env_arr(env[i]); //MALLOC
// 		if (env_list == NULL)
// 		{
// 			env_list = env_node_create(key, value);
// 			if (env_list == NULL)
// 				return NULL;
// 		}
// 		if (env_list != NULL)
// 			env_node_add_back(env_node_create(key, value), env_list);
// 		free(key);
// 		free(value);
// 		i++;
// 	}
// 	return (env_list);
// }

// char **array_dup(char **env)
// {
// 	char **dup;
// 	int env_len;
// 	int i;

// 	env_len = env_str_arr_size(env);
// 	i = 0;
// 	dup = (char **)malloc(sizeof(char *) * (env_len + 1));
// 	while (i < env_len)
// 	{
// 		dup[i] = ft_strdup(env[i]);
// 		i++;
// 	}
// 	dup[i] = NULL;
// 	return (dup);
// }

// static t_tools *init_tools(int argc, char **argv, char **env)
// {
// 	t_tools *tools;
// 	(void)argv;
// 	(void)argc;

// 	tools = (t_tools*)malloc(sizeof(t_tool));
// 	if (tools == NULL)
// 		return (NULL);
// 	tools->env = array_dup(env); //MALLOC
// 	tools->env_list = init_env_linked_list(env);
// 	//init_command_structure(argc, argv, tools);
// 	tools->number_of_pipes = 0;
// 	return (tools);
// }

t_command	**parser(t_tools *shell)
{
    t_token		**tkn_list;
    t_command	**cmd;

	cmd = NULL;
	tkn_list = tokeniser(shell->input, shell);
	if (shell->number_of_pipes == 0)
		cmd = create_simple_cmd(tkn_list, shell);
	else if (shell->number_of_pipes > 0)
		cmd = create_adv_cmd(tkn_list, shell);
	//printf("command %s\n", (*cmd)->args[0]);
	//printf("arg 1 %s\n", (*cmd)->args[2]);
	return (cmd);
}

// int	main(int argc, char **argv, char **env) // Tests the use of tokeniser, create_cmds.count_tokens, convert_token_id and beginning of parser
// {
// 	t_command	**cmd;
// 	t_command	*tmp;
// 	t_tool		*shell;
// 	char		*str;
// 	int			i;

// 	(void)argc;
// 	(void)argv;

// 	str = "ls | wc -l \"$USER\" ";
// 	i = 0;
// 	//shell = ft_calloc(1, sizeof(t_tool));
// 	shell = init_tools(argc,argv,env);
// 	shell->input = ft_strdup(str);
// 	cmd = parser(shell);
// 	tmp = *cmd;
// 	while (tmp != NULL)
// 	{
// 		while (tmp->args[i])
// 		{
// 			printf("Arg [%d]: %s\n", i, tmp->args[i]);
// 			if(tmp->args[i][0] == '>' && tmp->redirection->type == 3)
// 				printf("|output file|\n");
// 			else if (tmp->args[i][0] == '<' && tmp->redirection->type == 5)
// 				printf("<---- input file\n");
// 			i++;
// 		}
// 		tmp = tmp->next;
// 		if (tmp)
// 			printf("Next Command\n");
// 		i = 0;
// 	}
// 	return (0);
// }