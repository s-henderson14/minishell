#include "../include/minishell.h"

// typedef struct s_tools
// {
//     char *input;
//     char **env;
//     struct s_env_var *env_var;
//     t_command *command;
//    // t_token *history;
//     int number_of_pipes;

// }t_tool;

int glob_exit_status = 0;

static t_tools *init_tools(char **env)
{
	t_tools *tools;

	glob_exit_status = 0;
	tools = (t_tools *)malloc(sizeof(t_tools));
	if (tools == NULL)
		return (NULL);
	tools->input = NULL;
	tools->env = env;
	tools->env_list = NULL;
	tools->command_list= NULL;
	tools->number_of_pipes = 0;
	return (tools);
}
/*
static void shell_loop(t_tools *tools)
{
	char *line;

	while (1)
	{
		line = readline("minishell: "); //caller must free it when finished
		//check if input == NULL>> doesnt go to history
		if (line == NULL) // means it encounters EOF, ctrl-D
			exit(glob_exit_status);
		tools->input = line;
		//maybe add a condition which terminates the program immidiately??
		//check if input full with " ">> goes to history (PARSING PART??)
		//if parsing == succes
		//		execute
		add_history(tools->input);
		free(tools->input);
		tools->input = NULL;
		//free things.
	}
	exit(glob_exit_status);
}
*/
int main(int argc, char **argv, char **env)
{
	(void)argv;
	t_tools *tools;
	if (argc != 1)
	{
		printf("ERROR");
		exit(1);
	}
	tools = init_tools(env);
	//handle signals();
	tools->env_list = init_env_linked_list(env);
	env_list_print(tools->env_list);

	//shell_loop(tools);
}