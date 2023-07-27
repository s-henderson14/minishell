#include "../include/minishell.h"

t_command   *create_cmds(t_token **tkn_list)
{
    t_command	*cmd;
    t_token		*tkn;
	int			argc;
	int			i;

	i = 0;
    cmd = ft_calloc(1, sizeof(t_command));
	argc = count_tokens(tkn_list);
	cmd->args = ft_calloc(argc, sizeof(char *));
	tkn = *tkn_list;
	while (tkn != NULL)
	{	
		if (tkn->content != NULL)
			cmd->args[i] = tkn->content;
		else
			cmd->args[i] = convert_tkn_id(tkn->type);
		i++;
		tkn = tkn->next;
	}
	return(cmd);
}