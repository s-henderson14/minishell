#include "../include/minishell.h"

void	add_cmd_front(t_command **cmd_lst, t_command *new_cmd)
{
	new_cmd->next = *cmd_lst;
	*cmd_lst = new_cmd;
}

void	add_cmd_back(t_command **cmd_lst, t_command *new_cmd)
{
	t_command	*tmp;

	tmp = *cmd_lst;
	if (*cmd_lst == NULL)
	{	
		add_cmd_front(cmd_lst, new_cmd);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_cmd;
}


t_command	*create_simple_cmd(t_token **tkn_list, t_tool *shell)
{
	t_command	*cmd;
	t_token		*tkn;
	int			i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->args = ft_calloc(count_tokens(tkn_list), sizeof(char *));
	if (shell->number_of_redir >= 1)
			cmd->redirection = ft_calloc(1, sizeof(t_redirection *));
	tkn = *tkn_list;
	while (tkn != NULL)
	{
		if (tkn->content != NULL)
			cmd->args[i] = tkn->content;
		else
		{	
			//NOTE: edge case "ls > file1 > file2" will create file1 but only write into file2. We would have to say if shell->number_ of_redir > 1 then
			// the following literals would be created as files and only the last word (use a last word function) would be written into 
			cmd->args[i] = convert_tkn_id(tkn->type);
			cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
			cmd->redirection->file_name = tkn->next->content;
			cmd->redirection->type = tkn->type;
			if (tkn->next->type != 2 && tkn->next != NULL)
				exit(1);//error handle. NOTE: "ls > cd" will create a file called cd. So we dont have to distinguish between comand LITERALS and filename LITERALS
		}
		i++;
		tkn = tkn->next;
	}
	return (cmd);
}


// t_command	**create_cmd(t_token **tkn_list, t_tool *shell)
// {
// 	t_command	**cmd_list;
// 	t_command	**pipe_split;
// 	t_command	*cmd;
// 	t_token		*tkn;
// 	int			i;

// 	i = 0;
// 	cmd_list = ft_calloc(shell->number_of_pipes + 1, sizeof(t_command *));
// 	pipe_split = ft_split(shell->input, '|');
// 	while(i <= shell->number_of_pipes)
// 	{
// 		cmd = ft_calloc(1, sizeof(t_command));
// 		cmd->args = ft_calloc(word_count(pipe_split[i], ' '), sizeof(char *));
// 		if (ft_strchr(pipe_split[i], '>') || ft_strchr(pipe_split[i], '<'))
// 			cmd->redirection = ft_calloc(1, sizeof(t_redirection));
// 		tkn = *tkn_list;
// 		while (tkn != NULL)
// 		{
// 			if (tkn->content != NULL)
// 				cmd->args[i] = tkn->content;
// 			else if(tkn->type == 1)
// 				break;
// 			else if (tkn->type > 2)
// 			{
// 				cmd->args[i] = convert_tkn_id(tkn->type);
// 				if (tkn->next->content == 2)
// 				}
// 			}
// 			i++;
// 			tkn = tkn->next
// 		}
// 	}
// }
