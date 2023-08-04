#include "../../include/minishell.h"

int error_exit(char *s, int exit_status)
{
	glob_exit_status = exit_status;
	if (s == NULL)
		return (glob_exit_status);
	ft_putstr_fd(s, STDERR_FILENO);
	write(STDOUT_FILENO, "\n", 1);
	return (glob_exit_status);
}

char *protect(char *arg)
{
	if (arg == NULL)
	{
		perror("Error"); // so that the error message based on errno will be printed
		glob_exit_status = 1;
		exit(1);
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






