#include "../../include/minishell.h"

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
	//printf("new_path = %s\n", new_path);
	//printf("current_pwd = %s\n", current_pwd);
	if (chdir(new_path) == -1)
	{
		free(new_path); // i ll call exit anyways
		error_exit("cd: No such a file or directory\n", 1); //DONT EXIT!!!
	}
	//printf("pwd = %s\n", get_value_from_env_node("PWD", env_list));			
	change_value_of_env_key(new_path, "PWD", env_list);	//if i set this line, PWD changes
	change_value_of_env_key(current_pwd, "OLDPWD", env_list);	//oldpwd SET
	//printf("oldpwd = %s\n", current_pwd);
	//printf("pwd = %s\n", new_path);
	//printf("pwd = %s\n", get_value_from_env_node("PWD", env_list));	
	//env_list_print(env_list);
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
	//if (command->args[2] != NULL) //normally, if second arg is valid, then it ignores 3rd
	//	error_exit("cd: too many arguments\n");
	if (command->args[1] == NULL
		|| ft_strsame(command->args[1], "~") == 1)
	{
		target = get_value_from_env_node("HOME", env_list); //PROTECT
		//printf("target = %s\n", target);
	}
	else if (ft_strsame(command->args[1], "-") == 1) // ----OLDPWD
	{
		target = get_value_from_env_node("OLDPWD", env_list); //proteeect
	}
	else
	{
		target = command->args[1];
	}
	set_pwd_update_oldpwd(target, env_list);
	return (glob_exit_status);
}