#include "../../include/minishell.h"

int error_exit(char *s, int exit_status)
{
	if (s == NULL)
		return (exit_status);
	ft_putstr_fd(s, STDERR_FILENO);
	g_sig = exit_status;
	write(STDOUT_FILENO, "\n", 1);
	return (exit_status);
}

char *protect(char *arg)
{
	if (arg == NULL)
	{
		perror("Error"); // so that the error message based on errno will be printed
		g_sig = 1;
		return (NULL);
	}
	return (arg);
}

char **argv_duplicate_without_program_name(char **argv, int argc)
{
	char **dup;
	int i;

	i = 0;
	dup = (char **)malloc(sizeof(char *) * argc);
	if (dup == NULL)
		error_exit("Malloc failed\n", 1);
	while (i < argc - 1)
	{
		dup[i] = ft_strdup(argv[i + 1]);
		if (dup[i] == NULL)
			error_exit("Malloc failed\n", 1);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

char **array_dup(char **env)
{
	char **dup;
	int env_len;
	int i;

	env_len = env_str_arr_size(env);
	i = 0;
	dup = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (dup == NULL)
		error_exit("Malloc failed\n", 1);
	while (env[i] != NULL && i < env_len)
	{
		dup[i] = ft_strdup(env[i]);
		if (dup[i] == NULL)
			error_exit("Malloc failed\n", 1);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}





