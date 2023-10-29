#include "../../include/minishell.h"

char *find_upper_dir(char *current_dir)
{
	int len;
	char *upper_dir;

	len = ft_strlen(current_dir);
	while (len > 0)
	{
		if (current_dir[len - 1] == '/')
			break ;
		len--;
	}
	upper_dir = ft_substr(current_dir, 0, len);
	return (upper_dir);
}

void	initiate_oldpwd(char *value_to_oldpwd, t_env_node *env_list)
{
	t_env_node *oldpwd;

	oldpwd = env_node_create("OLDPWD", value_to_oldpwd);
	if (oldpwd == NULL)
	{
		return ;
	}
	env_node_add_back(oldpwd, env_list);
}

void set_pwd_update_oldpwd(char *new_path, t_env_node *env_list)
{
	char *current_pwd;

	if (check_key_exist("OLDPWD", env_list) == 0)
		initiate_oldpwd("", env_list);
	current_pwd = protect(getcwd(NULL, 0));				//get current_pwd
	if (chdir(new_path) == -1)
	{
		free(new_path); // i ll call exit anyways
		error_exit("mini_cd: No such a file or directory\n", 1); //DONT EXIT!!!
	}
	change_value_of_env_key(new_path, "PWD", env_list);	//if i set this line, PWD changes
	change_value_of_env_key(current_pwd, "OLDPWD", env_list);	//oldpwd SET
	free(current_pwd);
	free(new_path);
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

int mini_cd(t_tools *tools, t_command *command)
{
	char	*target;
	t_env_node	*env_list;

	env_list = tools->env_list;
	if (command->args[1] == NULL
		|| ft_strsame(command->args[1], "~") == 1)
	{
		target = get_value_from_env_node("HOME", env_list); //PROTECT
	}
	else if (ft_strsame(command->args[1], "..") == 1)
	{
		//printf("NOKTANOKTA\n");
		target = find_upper_dir(getcwd(NULL, 0));
	}
	else if (ft_strsame(command->args[1], ".") == 1)
		return (EXIT_SUCCESS);
	else if (ft_strsame(command->args[1], "-") == 1) // ----OLDPWD
	{
		target = get_value_from_env_node("OLDPWD", env_list); //proteeect
	}
	else
	{
		target = command->args[1];
	}
	printf("target = %s\n", target);
	set_pwd_update_oldpwd(target, env_list);
	return (EXIT_SUCCESS);
}