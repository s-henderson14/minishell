#include "../../include/minishell.h"

void	clean_split(char **arr)
{
	int	i;

	i = 0;
	if (arr[i])
	{	
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr);
}

void	clean_redirection(t_redirection *node)
{
	t_redirection	*nxt;

	if (!node)
		return ;
	while (node)
	{
		if (node->file_name)
			free(node->file_name);
		nxt = node->next;
		free(node);
		node = nxt;
	}
	free(node);
}

void clean_cmd_list(t_command **cmd_list)
{
	t_command	*nxt;
	t_command	*node;

	if (!cmd_list)
		return ;
	node = *cmd_list;
	while (node)
	{
		nxt = node->next;
		if (node->args)
			clean_split(node->args);
		if (node->redirection)	
			clean_redirection(node->redirection);
		free(node);
		node = nxt;
	}
	*cmd_list = NULL;
}

// void	clean_env_list(t_env_node **env)
// {
// 	t_env_node	*tmp;

// 	if (!env)
// 		return ;
// 	while (*env)
// 	{
// 		tmp = (*env)->next;
// 		free_env_node(*env);
// 		*env = tmp;
// 	}
// 	env = NULL;
// }