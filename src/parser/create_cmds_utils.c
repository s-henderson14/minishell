#include "../../include/minishell.h"

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

	i = 0; ////Example of "ls -l | grep libft" become "ls -l" "grep libft"
	count = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] != '|' || s[i] != '>' || s[i] != '<') //changed to remove pipes and redirections from command args
		{	
			while (s[i] && s[i] != c)
			{	
				i++;
				if (s[i] == c || s[i] == '\0')
					count++;
			}
		}
		else
			i++;// added as part of removing pipes and redirections from command args
	}
	return (count);
}

void init_cmd(t_command ***cmd_list, t_command **cmd, t_token **tkn_list)
{
	*cmd_list = ft_calloc(1, sizeof(t_command *));
	*cmd = ft_calloc(1, sizeof(t_command));
	(*cmd)->args = ft_calloc(count_tokens(tkn_list) + 1, sizeof(char *));
}

void assign_literal(t_command *cmd, t_token *tkn, int *index)
{
	cmd->args[*index] = ft_calloc(ft_strlen(tkn->content) + 1, sizeof(char));
	ft_strlcpy(cmd->args[*index], tkn->content, ft_strlen(tkn->content) + 1);
	*index += 1;
}

t_command *extract_cmd(t_token **tkn_list, t_tools *shell, int *repeater)
{
	t_command	*cmd;
	t_token		*tkn;
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (j++ != *repeater)
		tkn = tkn->next;
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->args = ft_calloc(count_tokens(tkn_list) + 1, sizeof(char *));
	redir_init(shell, cmd);
	tkn = *tkn_list;
	while (tkn != NULL)
	{
		if (tkn->type == 1)
			break ;
		else if (tkn->type > 2 && tkn->next->type == 2)
			add_redir(cmd, tkn);
		else if (tkn->content != NULL)
			assign_literal(cmd, tkn, &i);
		tkn = tkn->next;
	}
	if (tkn->type == 1 || tkn->type > 2)
		*repeater += 1;
	cmd->args[i] = NULL;
	return (cmd);
}