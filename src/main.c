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

static t_tools *init_tools(int argc, char **argv, char **env)
{
	t_tools *tools;
	(void)argv;
	(void)argc;

	glob_exit_status = 0;
	tools = (t_tools *)malloc(sizeof(t_tools));
	if (tools == NULL)
		return (NULL);
	tools->input = NULL;
	tools->env = array_dup(env); //MALLOC
	tools->env_list = init_env_linked_list(env);
	//init_command_structure(argc, argv, tools);
	tools->number_of_pipes = 0;
	return (tools);
}

static void shell_loop(t_tools *tools)
{
	char *line;

	while (1)
	{
		line = readline("minishell: "); //caller must free it when finished
		//check if input == NULL>> doesnt go to history
		if (line == NULL) // means it encounters EOF, ctrl-D
		{
			free(line);
			error_exit("bad user input", 1); //??
		}	
		else if (line[0] != '\0')
		{
			tools->input = line;
			add_history(tools->input);
			//check if input full with " ">> goes to history (PARSING PART??)
			//IF PARSING == SUCCESS
			//		EXECUTE
			tools->command_list = init_command_list(line, tools);
			//printf("%s\n", tools->command_list->args[0]);
			choose_builtin(tools);
			free(tools->input);
			tools->input = NULL;
			//free things.
		}
	}
}

int main(int argc, char **argv, char **env)
{
	t_tools *tools;
	// (void)argv;
	// (void)argc;
		// if (argc == 1)
	// {
	// 	printf("ERROR, argc = 1");
	// }
	tools = init_tools(argc, argv, env);
	//handle signals();
	//tools->env_list = init_env_linked_list(env);
	//env_list_print(tools->env_list); //works until here
	//init_command_structure(argv, argc, tools);
	//printf("%s\n", tools->command_list->args[0]);
	//choose_builtin(argv, tools);
	//define a command here to test built-ins.

	shell_loop(tools);
}