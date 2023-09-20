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

void choose_builtin(t_tools *tools)
{
	t_command *command;

	command = tools->command_list;
	if (ft_strsame(command->args[0], "cd") == 1)
		mini_cd(tools, command);
	if (ft_strsame(command->args[0], "pwd") == 1)
		mini_pwd(tools);
	if (ft_strsame(command->args[0], "echo") == 1)
		mini_echo(tools, command);
	if (ft_strsame(command->args[0], "env") == 1)
		mini_env(tools, command);
	if (ft_strsame(command->args[0], "exit") == 1)
		mini_exit(tools, command);
	if (ft_strsame(command->args[0], "unset") == 1)
		mini_unset(tools, command);
	if (ft_strsame(command->args[0], "export") == 1)
		mini_export(tools, command);
	else
		return ;
}