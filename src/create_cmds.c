#include "../include/minishell.h"

t_command   *create_cmds(t_token **tkn_list, t_tool *shell)
{
    t_command	*cmd;
    t_token		*tkn;
	int			argc;
	int			i;

	i = 0;
    cmd = ft_calloc(1, sizeof(t_command));
	argc = count_tokens(tkn_list);
	cmd->args = ft_calloc(argc, sizeof(char *));
	cmd->redirection = ft_calloc(1, sizeof(t_redirection));
	tkn = *tkn_list;
	while (tkn != NULL)
	{	
		if (tkn->content != NULL)
			cmd->args[i] = tkn->content;
		else if (tkn->type > 2)
		{	
			cmd->args[i] = convert_tkn_id(tkn->type);
			if (tkn->next->type == 2)
			{	
				cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
				cmd->redirection->file_name = tkn->next->content;
			}
			i++;
			tkn = tkn->next;
		}
	}
	return (cmd);
}