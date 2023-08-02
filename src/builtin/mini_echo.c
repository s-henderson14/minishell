#include "../../include/minishell.h"

/*
**	Prints strings of char **args array
**	param i : starting index of the strings array for printing
*/
void print_arguments(int i, t_tools *tools, t_command *command)
{

	char **args;

	args = command->args;
	while (args[i] != NULL)
	{
		if (ft_strsame(args[i], "~") == 1)
			print_value("HOME", tools);
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
	int j;
	int print_newline;

	(void)tools;
	args = command->args;
	i = 1;
	print_newline = 1;
	while (args[i] != NULL && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		if (args[i][j] != '\0' && args[i][j] != 'n')
			break ;
		while (args[i][j] != '\0' && args[i][j] == 'n') // -nnnnnn
			j++;
		if (args[i][j] == '\0')
		{
			print_newline = 0;
			i++;
			break ;
		}
		i++;
	}
	print_arguments(i, tools, command);
	if (print_newline == 1)
		printf("\n");
	return (glob_exit_status);
}
