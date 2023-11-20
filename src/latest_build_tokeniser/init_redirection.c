#include "../../include/minishell.h"

void	add_redir(t_command *cmd, t_token *tkn)
{
	t_redirection *redir;
	
	redir = ft_calloc(1, sizeof(t_redirection));





	redir->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	ft_memcpy(redir->file_name, tkn->next->content, ft_strlen(tkn->next->content) + 1);
	//redir->file_name = tkn->next->content;
	redir->type = tkn->type;



	// cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
	// cmd->redirection->file_name = tkn->next->content;
	//ft_strlcpy(cmd->redirection->file_name, tkn->next->content, ft_strlen(tkn->next->content));
	//printf("file name %s\n", cmd->redirection->file_name);
	// cmd->redirection->type = tkn->type;
	if (tkn->next->type != 2 && tkn->next != NULL)
		exit(1); // Handle error
	add_redir_back(cmd->redirection,redir);
	// cmd->redirection = redir;
	// redir = cmd->redirection->next;
}

void	redir_init(t_tools *shell, t_command *cmd)
{
	if (shell->number_of_redir >= 1)
	{
		cmd->redirection = ft_calloc(1, sizeof(t_redirection));
		cmd->redirection->file_name = NULL;
		cmd->redirection->type = 0;
		cmd->redirection->next = NULL;
	}
	if (shell->number_of_redir == 0)
		cmd->redirection = NULL;
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
	if (redir_lst == NULL)
	{	
		add_redir_front(redir_lst, new_redir);
		return ;
	}
  	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_redir;
	new_redir->next = NULL;
}

//void	*ft_memcpy(void *dst, const void *src, size_t n)