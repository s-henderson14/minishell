#include "../../include/minishell.h"

int check_arg_digit(char *arg)
{
	if (arg == NULL)
		return (0);
	while (*arg != '\0')
	{
		if (ft_isdigit(*arg) != 1)
			return (0);
		arg++;
	}
	return (1);
}

/*
**	This function traverses within env_linked_list,
**	tries to find the key element equal to char *key,
**	if finds, return its value
*/
char	*get_value_from_env_node(char *key, t_env_node *env_list)
{
	char *value;

	if (check_key_exist(key, env_list) == 0)
		return (NULL);
	while (env_list != NULL)
	{
		if (ft_strsame(key, env_list->key) == 1)
		{
			value = ft_strdup(env_list->value);
			return (value);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

/*
** 	Searchs equal sign in given string. If finds returns its index position. Else, -1
*/
int find_equal_sign(char *arg)
{
	int i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int is_builtin(t_command *command)
{
	if (ft_strsame(command->args[0], "echo") == 1
			|| ft_strsame(command->args[0], "cd") == 1
			|| ft_strsame(command->args[0], "pwd") == 1
			|| ft_strsame(command->args[0], "env") == 1
			|| ft_strsame(command->args[0], "exit") == 1
			|| ft_strsame(command->args[0], "export") == 1
			|| ft_strsame(command->args[0], "unset") == 1)
	{
		return (1);
	}
	return (0);
}