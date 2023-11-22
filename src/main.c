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

int g_sig = 0;

static t_tools *init_tools(int argc, char **argv, char **env)
{
	t_tools *tools;
	(void)argv;
	(void)argc;

	//signal_init();
	tools = (t_tools *)malloc(sizeof(t_tools));
	if (tools == NULL)
		return (NULL);
	tools->input = NULL;
	tools->number_of_pipes = 0;
	tools->number_of_redir = 0;
	tools->env = array_dup(env); //MALLOC
	tools->env_list = init_env_linked_list(env);
	tools->token_list = NULL;

	//printf("%s \n %s \n", tools->env_list->key, tools->env_list->next->key);
	//init_command_structure(argc, argv, tools);
	// tools->number_of_pipes = 0;
		// printf("pipes= %d\n", tools->number_of_pipes);
	return (tools);
}

static void shell_loop(t_tools *tools) // return int for errors
{
	char *line;
	t_command **cmd_list;

	while (1)
	{
		signal_init();
		line = readline("\033[0;35m----->\033[1;36mMINISHELL&: \033[1;33m"); //caller must free it when finished
		if (line == NULL) // means it encounters EOF, ctrl-D
		{
			free(line);
			return ;
			// error_exit("bad user input", 1); //??
			// exit(1);
		}
		else if (line[0] != '\0')
		{
			tools->input = line;
			add_history(tools->input);
			cmd_list = parser(tools);
			tools->command_list = *(cmd_list);
			//printf("command=%s\n", tools->command_list->args[0]);
			 // printf("command args = %s %d %s %d %s\n", tools->command_list->args[0], tools->command_list->redirection->type,
			// 	  tools->command_list->redirection->next->file_name, tools->command_list->redirection->next->type, tools->command_list->redirection->next->file_name);
			execute(tools);
			tkn_list_free(tools->token_list);
			//command_list_free(tools->command_list);
			clean_cmd_list(&tools->command_list);
			tools->command_list = NULL;
			free(line);
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
	shell_loop(tools);
	free_double_arr(tools->env);
	env_list_free(tools->env_list);
	free(tools);
	clear_history();
	return(g_sig);
}