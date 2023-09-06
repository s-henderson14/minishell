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

int	word_counter(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{	
			i++;
			if (s[i] == c || s[i] == '\0')
				count++;
		}
	}
	return (count);
}

t_command	**create_simple_cmd(t_token **tkn_list, t_tool *shell)
{
	t_command	**cmd_list;
	t_command	*cmd;
	t_token		*tkn;
	int			i;

	i = 0;
	cmd_list = ft_calloc(1, sizeof(t_command *));
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
			redir_init(cmd, tkn, &i);
		i++;
		tkn = tkn->next;
	}
	cmd->args[i] = NULL;
	add_cmd_front(cmd_list, cmd);
	return (cmd_list);
}


t_command	**create_adv_cmd(t_token **tkn_list, t_tool *shell)
 {
	t_command	**cmd_list;
	char	**pipe_split;
	t_command	*cmd;
	t_token		*tkn;
	int			i;

	i = 0;
	cmd_list = ft_calloc(shell->number_of_pipes + 1, sizeof(t_command *));
	pipe_split = ft_split(shell->input, '|');
	while(i <= shell->number_of_pipes)
	{
		cmd = ft_calloc(1, sizeof(t_command));
		cmd->args = ft_calloc(word_counter(pipe_split[i], ' '), sizeof(char *));
		if (shell->number_of_redir > 0)
			cmd->redirection = ft_calloc(shell->number_of_redir, sizeof(t_redirection));
		tkn = *tkn_list;
		while (tkn != NULL)
		{
			if (tkn->content != NULL)
				cmd->args[i] = tkn->content;
			else if(tkn->type == 1)
			{
				cmd->args[i] = "|";
				break ;
			}
			else if (tkn->type > 2)
				redir_init(cmd, tkn, &i);
			i++;
			tkn = tkn->next;
		}
		add_cmd_back(cmd_list, cmd);
	}
	return (cmd_list);
}
	
	//NOTE: edge case "ls > file1 > file2" will create file1 but only write into file2. We would have to say if shell->number_ of_redir > 1 then
	// the following literals would be created as files and only the last word (use a last word function) would be written into 