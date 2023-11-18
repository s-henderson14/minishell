#include "../../include/minishell.h"

int	mini_exit(t_command *command)
{
	ft_putendl_fd("exit", STDERR_FILENO);
	if (command->args[1] == NULL)
		exit(0);
	if (command->args[0] != NULL && command->args[1] != NULL)
	{
		if (check_arg_digit(command->args[1]) != 1)
		{
			ft_putendl_fd("bash: exit: numeric argument required",
				STDERR_FILENO);
			exit(255);
		}
		if (ft_atoi(command->args[1]) < 256
			&& ft_atoi(command->args[1]) > 0)
			exit(ft_atoi(command->args[1]));
		else if (ft_atoi(command->args[1]) > 255)
		{
			ft_putendl_fd("Exit statuses fall between 0 and 255",
				STDERR_FILENO);
			exit(2);
		}
	}
	return (EXIT_SUCCESS);
}
