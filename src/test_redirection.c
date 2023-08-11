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


void decide_redirection_type(t_command *command)
{
    t_redirection *redirection;

    redirection = command->redirection;
    if (ft_strsame(redirection->token_name, "<") == 1)
        redirection->type = LESS;
    else if (ft_strsame(redirection->token_name, ">") == 1)
        redirection->type = GREAT;
    else if (ft_strsame(redirection->token_name, ">>") == 1)
        redirection->type = GREAT_GREAT;
    else if (ft_strsame(redirection->token_name, "<<") == 1)
        redirection->type = LESS_LESS;
}

t_redirection *init_redirection(t_command *command)
{
	t_redirection *redirection;

    if (command->args[2] == NULL && command->args[3] == NULL)
        return (NULL);
	redirection = (t_redirection *)malloc(sizeof(t_redirection));
	if (redirection == NULL)
		return (NULL);
	redirection->file_name = ft_strdup(command->args[3]);
    redirection->token_name = ft_strdup(command->args[4]);
	decide_redirection_type(command);
	redirection->next = NULL;
	return (redirection);
}

