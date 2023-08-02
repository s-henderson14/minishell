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

int mini_exit(t_tools *tools, t_command *command)
{
	int exit_code;

	(void)tools;
	exit_code = 0;
	ft_putendl_fd("exit", STDERR_FILENO);
	if (command->args[0] != NULL && command->args[1] != NULL)
	{
		if (command->args[2] != NULL)
		{
			ft_putendl_fd("bash: exit: too many arguments", STDERR_FILENO);
			glob_exit_status = 1;
			return (1);
		}
		if (check_arg_digit(command->args[1]) == 1
			&& ft_atoi(command->args[1]) < 256 && ft_atoi(command->args[1]) > 0)
		{
			exit_code = ft_atoi(command->args[1]);
		}
		else if (check_arg_digit(command->args[1]) == 1
			&& ft_atoi(command->args[1]) > 255)
		{
			ft_putendl_fd("Exit statuses fall between 0 and 255", STDERR_FILENO);
			exit_code = 2; 
		}
		else if (check_arg_digit(command->args[1]) != 1)
		{
			ft_putendl_fd("bash: exit: numeric argument required", STDERR_FILENO);
			exit_code = 255;
		}

		glob_exit_status = exit_code;
		exit(exit_code);
	}
	return (0);
}