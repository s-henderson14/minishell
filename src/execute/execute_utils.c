#include "../../include/minishell.h"

char *join_command_to_path(char *path, char *main_command)
{
	char *path_with_slash_at_the_end;
	char *joined_command;

	path_with_slash_at_the_end = ft_strjoin(path, "/"); //MALLOC
	if (path_with_slash_at_the_end == NULL)
		return (NULL);
	joined_command = ft_strjoin(path_with_slash_at_the_end, main_command);
	free(path_with_slash_at_the_end);
	if (joined_command == NULL)
		return (NULL);
	return (joined_command);
}

char **get_paths(t_tools *tools)
{
	char **path_arr;
	char *path_str;

	path_str = get_value_from_env_node("PATH", tools->env_list); //MALLOC
	if (path_str == NULL)
		return(ft_putendl_fd("Path can not be found", STDERR_FILENO), NULL);
	path_arr = ft_split(path_str, ':'); //MALLOC
	free(path_str);
	if (path_arr == NULL)
		return (NULL);
	return (path_arr);
}

static char *try_access_path(t_command *command, char **path_arr)
{
	int	i;
	char *full_path_command;
	char *current_dir;

	i = 0;
	current_dir = ft_strjoin(command->args[0], "./");
	if (current_dir == NULL)
		return NULL;  // ?????
	if (access(current_dir, F_OK) == 0)
	{
		return (current_dir);
	}
	while (path_arr[i] != NULL)
	{
		full_path_command = join_command_to_path(path_arr[i], command->args[0]);
		//printf("%s\n", full_path_command);
		if (full_path_command == NULL)
			error_exit("execute_child failed", 1);
		if (access(full_path_command, F_OK) == 0)
			return (full_path_command);
		free(full_path_command);
		i++;
	}
	return (NULL);
}
/*
**	execute_child() first searchs the command in current directory.
**	If finds, does execution, otherwise it searchs the command in PATH
*/
int call_execve(t_tools *tools, t_command *command)
{
	char **path_arr;
	char *full_path_command;

	path_arr = get_paths(tools);
	full_path_command = try_access_path(command, path_arr);
	if (full_path_command == NULL)
	{
		error_exit("command not found", 127);
		return (127);
	}
	execve(full_path_command, command->args, tools->env);
	free(full_path_command);
	//free all
	//exit code?
	error_exit("child exec bad", 1);
	return (EXIT_FAILURE);
}
