#include "../../include/minishell.h"

t_command	**create_simple_cmd(t_token **tkn_list, t_tools *shell)
{
	t_command	**cmd_list;
	t_command	*cmd;
	t_token		*tkn;
	int			i;

	i = 0;
	cmd_list = ft_calloc(1, sizeof(t_command *));
	cmd = ft_calloc(1, sizeof(t_command));
	printf("argc: %d\n", count_tokens(tkn_list));
	cmd->args = ft_calloc(count_tokens(tkn_list) + 1, sizeof(char *));
	if (shell->number_of_redir >= 1)
			cmd->redirection = ft_calloc(shell->number_of_redir, sizeof(t_redirection *));
	tkn = *tkn_list;
	while (tkn != NULL)
	{
		if (tkn->type > 2 && tkn->next->type == 2)
		{	
			redir_init(cmd, tkn);
			tkn = tkn->next;
		}
		else if (tkn->content != NULL)
		{
			cmd->args[i] = tkn->content;
			i++;
		}
		tkn = tkn->next;
	}
	cmd->args[i] = NULL;
	add_cmd_front(cmd_list, cmd);
	return (cmd_list);
}


t_command	**create_adv_cmd(t_token **tkn_list, t_tools *shell)
 {
	t_command	**cmd_list;
	char	**pipe_split;
	t_command	*cmd;
	t_token		*tkn;
	int			i;
	int			j;

	i = 0;
	j = 0;
	cmd_list = ft_calloc(shell->number_of_pipes + 1, sizeof(t_command *)); //allocate memory for a list of commands structs
	pipe_split = ft_split(shell->input, '|');                              // split the user input based on pipes "ls | wc -l" becomes "ls" "wc -l"
	//printf("%s %s %s %s\n", pipe_split[0], pipe_split[1], pipe_split[2], pipe_split[3]);//, pipe_split[3]);
	tkn = *tkn_list;                 									   // make our tmp token equal to the head of our token_list. In this example head tkn = "ls"
	while (j <= shell->number_of_pipes)                                   // 1 pipe present equals 2 commands and if i starts at 0 then we run our while loop for two rounds
	{
		cmd = ft_calloc(1, sizeof(t_command));                             // allocate space for a command struct
		cmd->args = ft_calloc((word_counter(pipe_split[j], ' ') - shell->number_of_redir) + 1, sizeof(char *)); // allocate space for command arguments ------CHANGE HOW WORD COUNTER COUNTS
		if (shell->number_of_redir > 0)                                              // if we have redirections logged 
			cmd->redirection = ft_calloc(shell->number_of_redir, sizeof(t_redirection));  // allocate space for redirection
		while (tkn != NULL)              // while we are not at the end of our list
		{
			if (tkn->type > 2 && tkn->next->type == 2)
			{	
				redir_init(cmd, tkn);
				tkn = tkn->next;
			}
			else if (tkn->content != NULL && tkn->type == 2)    // if token is a literal i.e not a redirection
			{	
				cmd->args[i] = tkn->content;  // assign the literal to args
				i++;
			}
			else if(tkn->type == 1)           // if 
			{
				//cmd->args[i] = "|";//Changed to remove pipes and redirections from command args
				tkn = tkn->next;
				break ;
			}
			tkn = tkn->next;
		}
		add_cmd_back(cmd_list, cmd);
		j++;
		i = 0;
	}
	return (cmd_list);
}
	
	//NOTE: edge case "ls > file1 > file2" will create file1 but only write into file2. We would have to say if shell->number_ of_redir > 1 then
	// the following literals would be created as files and only the last word (use a last word function) would be written into 