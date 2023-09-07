

CREATING A COMMAND WITHOUT PIPES

void	add_redir_front(t_redirection **redir_lst, t_redirection *new_redir)
{
	new_redir->next = *redir_lst;
	*redir_lst = new_redir;
}

void	add_redir_back(t_redirection **redir_lst, t_redirection *new_redir)
{
	t_redirection	*tmp;

	tmp = *redir_lst;
	if (*redir_lst == NULL)
	{	
		add_redir_front(redir_lst, new_redir);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_redir;
}

t_command	*create_simple_command(t_token **tkn_list, t_tools *shell)
{
	t_command		*cmd;
	t_token			*tkn;
	t_redirection **redirections;
	int			i;

	i = 0;
	cmd = ft_calloc(1, sizeof(t_command));
	cmd->args = ft_calloc(count_tokens(tkn_list), sizeof(char *));
	if (shell->number_of_redir > 0)
			cmd->redirection = ft_calloc(shell->number_of_redir, sizeof(t_redirection *));
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
			if (cmd->args[i][0] == '>' && ft_strlen(cmd->args[i] == 2))
				cmd->redirection->type = 4
			else if (cmd->args[i][0] == '>' && ft_strlen(cmd->args[i] == 1)
				cmd->redirection->type = 3;
			else if (cmd->args[i][0] == '<' && ft_strlen(cmd->args[i] == 2))
				cmd->redirection->type = 6
			else if (cmd->args[i][0] == '<' && ft_strlen(cmd->args[i] == 1)
				cmd->redirection->type = 5;
			if (tkn->next->type != 2 && tkn->next != NULL)
				exit(1);//error handle. NOTE: "ls > cd" will create a file called cd. So we dont have to distinguish between comand LITERALS and filename LITERALS
			cmd->redirection->file_name = ft_calloc(ft_strlen(tkn->next->content), sizeof(char));
			cmd->redirection->file_name = tkn->next->content;
			add_redir_back(redir_lst, cmd->redirection);

		}
		i++;
		tkn = tkn->next;
	}
	return (cmd);
}

Example. "ls -la > output.txt"

At this stage we have a token list which should consist of 4 count_tokens:

Token 1          Token 2            Token 3            Token 4
content = "ls"|	  content = "-la"|   content = null |   content = "output.txt"
type    = 2	  |   type	= 2	     |   type	 = 3	|   type    = 2


Firstly declaring the necessary components for our function:

	+ t_command *cmd - to store our command struct

	+ t_token 	*tkn - to traverse our list of tokens

	+ int 		i    - to iterate through our commands array of arguments

	+ t_redirection	*re

Then allocating memory for these components:

	+ cmd = ft_calloc(1, sizeof(t_command));

	+ tkn = *tkn_list;

	+ if (shell->number_of_redir >= 1)
			cmd->redirection = ft_calloc(1, sizeof(t_redirection));
