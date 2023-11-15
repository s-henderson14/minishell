#include "../../include/minishell.h"

/*
**	Prints strings of char **args array
**	param i : starting index of the strings array for printing
*/
void print_arguments(int i, t_tools *tools, t_command *command)
{
	char **args;
	//char *expanded;

	args = command->args;
	while (args[i] != NULL)
	{
		if (ft_strsame(args[i], "~") == 1)
			print_value("HOME", tools);
		else if (ft_strsame(args[i], "?") == 1)
			printf("%s\n", ft_itoa(g_sig)); //MALLOCCC

		// else if (check_first_char_dollar(args[i]) == 1)
		// {
		// 	expanded = expand_string(args[i], tools);
		// 	printf("%s", expanded);
		// 	free(expanded);
		// }
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
	return (EXIT_SUCCESS);
}
