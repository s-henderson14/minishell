#include "../../include/minishell.h"

void	redir_init(t_command *cmd, t_token *tkn)
{
	t_redirection *redir;
	
	redir = cmd->redirection;
	redir->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	redir->file_name = tkn->next->content;
	redir->type = tkn->type;
	printf("Token Type:%d\n", tkn->type);
	// cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	// cmd->redirection->file_name = tkn->next->content;
	//ft_strlcpy(cmd->redirection->file_name, tkn->next->content, ft_strlen(tkn->next->content));
	//printf("file name %s\n", cmd->redirection->file_name);
	// cmd->redirection->type = tkn->type;
	if (tkn->next->type != 2 && tkn->next != NULL)
		exit(1); // Handle error
	add_redir_back(cmd->redirection, redir);
	// cmd->redirection = redir;
	// redir = cmd->redirection->next;
}

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
	if (redir_lst->file_name == NULL)
	{	
		add_redir_front(redir_lst, new_redir);
		return ;
	}
  	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_redir;
	new_redir->next = NULL;
}