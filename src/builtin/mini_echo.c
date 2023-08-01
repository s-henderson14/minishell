#include "../../include/minishell.h"

void print_home(char *home, t_tools *tools)
{
	t_env_node *env_list;
	char *home_value;

	env_list = tools->env_list;
	home_value = get_value_from_env_node(home, env_list); //NOT NECESSARY AT ALL!!!
	printf("%s");
}

/*
**	Prints strings of char **args array
**	param i : starting index of the strings array for printing
*/
void print_arguments(int i, t_command *command)
{
	char **args;

	args = command->args;
	while (args[i] != NULL)
	{
		if (ft_strsame(args[i], "~") == 1)
			print_home("HOME", tools);
		else
			printf("%s", args[i]);
		if (args[i + 1] != NULL)
			printf(" ");
		i++;
	}
}

int mini_echo(t_tools *tools, t_command *command)
{
	char **args;
	int i;
	int print_newline;

	args = command->args;
	i = 1
	print_newline = 1;
	while (args[i] != NULL && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		if (args[i][j] != '\0' && args[i][j] != 'n')
			break ;
		while (args[i][j] != '\0' && args[i][j] == 'n') // -nnnnnn
			j++;
		if (args[i][j] == '\0')
		{
			print_newline = 0;
			break ;
		}
		i++;
	}
	print_arguments(i, command);
	if (print_newline == 1)
		printf("\n");
}
