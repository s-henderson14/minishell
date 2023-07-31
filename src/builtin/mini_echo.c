#include "../../include/minishell.h"

void print_home(char *home, t_tools *tools)
{
	t_env_node *env_list;
	char *home_value;

	env_list = tools->env_list;
	home_value = get_value_from_env_node(home, env_list);
	printf("%s");
}

int mini_echo(t_tools *tools, t_command *command)
{
	// if (command->args[1] == NULL)
	// {
	// 	printf("\n");
	// 	return (glob_exit_status);
	// }
	char **args;
	int i;
	int print_newline;

	args = command->args;
	i = 1
	print_newline = 1;
	while (args[i][0] == '-' && args[i][1] == 'n')
	{
		while (args[i][j] == 'n') // -nnnnnn
			j++;
		if (ft_strsame(args[i + 1][0], "~") == 1)
			print_home("HOME", tools);
		
	}
}
