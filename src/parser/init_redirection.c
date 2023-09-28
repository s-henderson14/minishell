#include "../../include/minishell.h"

void	redir_init(t_command *cmd, t_token *tkn)
{
	//cmd->args[*index] = convert_tkn_id(tkn->type);Changed to remove pipes and redirection from args
	cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	cmd->redirection->file_name = tkn->next->content;
	//printf("file name %s\n", cmd->redirection->file_name);
	cmd->redirection->type = tkn->type;
	if (tkn->next->type != 2 && tkn->next != NULL)
		exit(1); // Handle error
}