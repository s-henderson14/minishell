#include "minishell.h"

/* Prints all the elements in t_tool struct
*/
void print_tools(t_tools *tools)
{
	int size;

	size = env_list_size(tools);
	printf("Number of pipes: %d\n", tools->number_of_pipes);
	while (size > 0)
}