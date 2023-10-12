#include "../../include/minishell.h"

void	redir_init(t_command *cmd, t_token *tkn)
{
	t_redirection *redir;

	redir = NULL;
	//
	cmd->redirection->file_name = tkn->next->content;
	cmd->redirection->type = tkn->type;
	printf("Token Type:%d\n", tkn->type);
	// cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	// cmd->redirection->file_name = tkn->next->content;
	//ft_strlcpy(cmd->redirection->file_name, tkn->next->content, ft_strlen(tkn->next->content));
	//printf("file name %s\n", cmd->redirection->file_name);
	// cmd->redirection->type = tkn->type;
	if (tkn->next->type != 2 && tkn->next != NULL)
		exit(1); // Handle error
	printf("count_nodes = %d\n", count_nodes(cmd->redirection));
	redir = ft_calloc(1, sizeof(t_redirection));
	if (redir == NULL)
		return ;
	redir->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	add_redir_back(cmd->redirection, redir);
	printf("count_nodes = %d\n", count_nodes(cmd->redirection));
}

//probably we dont need this since we have a initial node (cmd->redir)
void	add_redir_front(t_redirection *redir_lst, t_redirection *new_redir)
{
	new_redir->next = redir_lst;
	redir_lst = new_redir;
}


void	add_redir_back(t_redirection *redir_lst, t_redirection *new_redir)
{
	t_redirection	*tmp;

	tmp = redir_lst;
	printf("file name check: %s\n", redir_lst->file_name);
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_redir;
	new_redir->next = NULL;
}

int count_nodes(t_redirection *redirection)
{
	t_redirection *temp;
	int count;

	count = 0;
	temp = redirection;
	while (temp != NULL)
	{
		count++;
		temp = temp->next;
	}
	return count;
}