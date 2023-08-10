#include "../include/minishell.h"

// typedef struct s_redirection
// {
//     char            *file_name;
//     t_token_type    type; //if it s <<, heredoc, call heredoc f()
//     struct s_redirection *next; //ls > output.txt < input.txt
//                                 //just like above, we might have multiple redir. in a command,
//                                 //thats why we have a pointer to redirection.
// }t_redirection;

// t_token_type choose_token_type(t_redirection *redirection, t_command *command, int index_token)
// {
// 	redirection->type = PIPE;
// 	while (redirection->type <= LESS_LESS)
// 	{
// 		if (command->args[index_token] == redirection->type)
// 		{
// 			init_redirection()
// 		}
// 		redirection->type++;
// 	}
// 	return (0);
// }



// t_redirection *init_redirection(t_tools *tools, t_command *command)
// {
// 	t_redirection *redirection;
// 	(void)tools;

// 	redirection = (t_redirection *)malloc(sizeof(t_redirection));
// 	if (redirection == NULL)
// 		return (NULL);
// 	redirection->file_name = ft_strdup(command->args[3]);
// 	redirection->type = choose_token_type(redirection, command, 3); //later str_same will be used to compare 
// 										//redir->type and one of the symbols (< > << etc)
// 	redirection->next = NULL;
// 	return (redirection);
// }

