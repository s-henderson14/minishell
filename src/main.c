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
	tools->interactive = 1;
	//init_command_structure(argc, argv, tools);
	// tools->number_of_pipes = 0;
		// printf("pipes= %d\n", tools->number_of_pipes);
	return (tools);
}

static void shell_loop(t_tools *tools)
{
	char *line;
	t_command **cmd_list;

	while (signal_flag == 0)
	{
		signal_flag = init_signal();
		line = readline("\033[0;35m----->\033[1;36mMINISHELL&: \033[1;33m"); //caller must free it when finished
		//check if input == NULL>> doesnt go to history
		// if (signal_flag == 2)
		// 	continue ;
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
			//tools->command_list = init_command_list(line, tools); //temp, testing purpose
			cmd_list = parser(tools);
			tools->command_list = *(cmd_list);
			//printf("command args = %s %s \n", tools->command_list->args[0], tools->command_list->args[1]);
			execute(tools);
			//printf("EXEC FINISH\n");
			//command_list_free(tools->command_list);
			tools->command_list = NULL;
			free(tools->input);
			tools->input = NULL;
			//free things.
			//printf("--------");
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
	signal_flag = 0;
	shell_loop(tools);
}