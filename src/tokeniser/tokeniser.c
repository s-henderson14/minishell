#include "../../include/minishell.h"

t_token **tokeniser(char *input, t_tools*shell)
{
	t_token	**tkn_list;
	t_token	*tkn;
	char	**split_input;
	int		i;

	i = 0;
	shell->number_of_pipes = 0; //GUL ADDED THIS LINE!!! (numb of pipe and redir need to be init before using)
	shell->number_of_redir = 0;	//GUL ADDED THIS LINE!!!
	tkn_list = ft_calloc(1, sizeof(t_token *));
	if (!tkn_list)
		return (NULL);
	split_input = ft_split(input, ' ');
	if(!split_input)
		return (free(tkn_list), NULL);
	while (split_input[i])
	{	
		tkn = ft_calloc(1, sizeof(t_token));
		if (!tkn)
		{
			//clean split()
			//free list()
			//return(NULL);
		}
		if(ft_isalpha(split_input[i][0]) || ft_isdigit(split_input[i][0]) || split_input[i][0] == 45)
		{	
			tkn->type = LITERAL;
			tkn->content = get_literal_token(split_input[i]);
		}
		else if (double_found(split_input[i]) && dollar_sign_found(split_input[i]))
		{
			tkn->type = LITERAL;
			tkn->content = expand(split_input[i], shell->env_list);
			printf("%s\n", tkn->content);
		}
		else
			assign_token_type(tkn, split_input[i]);
			//tkn->content = get_literal_token(split_input[i]); Changed to remove Pipes and Redirections from command args
		if (tkn->type == PIPE)
			shell->number_of_pipes += 1;
		if (tkn->type > 2)
			shell->number_of_redir += 1;
		add_token_back(tkn_list, tkn);
		i++;
	}
	//printf("pipes= %d\n", shell->number_of_pipes);
	//printf("%s %s %s %s %s\n", (*tkn_list)->content, (*tkn_list)->next->content,
	//	(*tkn_list)->next->next->content, (*tkn_list)->next->next->next->content, (*tkn_list)->next->next->next->next->content);
	return (tkn_list);
}

// int	main(int argc, char **argv) //THIS TESTING PART IS FOR GUL(just wanted to get str from command line, so that i could use another commands to test)
// {
// 	t_token	**tkn_list;
// 	t_token	*tmp;
// 	t_tools	*shell;
// 	char	*str;
// 	(void)argc;

// 	str = "ls -la > out";
// 	str = argv[1];
// 	shell = ft_calloc(1, sizeof(t_tools));
// 	tkn_list = tokeniser(str, shell);

// 	tmp = *tkn_list;
// 	while (tmp != NULL)
// 	{
// 		printf("Token Content: %s\nToken ID: %d\n",tmp->content, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	//printf("redir token_name %s\n", shell->redirection->token_name);
// 	printf("No. of Pipes: %d\nNo. of Redirections: %d\n", shell->number_of_pipes, shell->number_of_redir);
// 	free(tkn_list);
// 	free(shell);
// 	return (0);
// }


// int	main()
// {
// 	t_token	**tkn_list;
// 	t_token	*tmp;
// 	t_tools	*shell;
// 	char	*str;

// 	str = "ls -la > out";
// 	shell = ft_calloc(1, sizeof(t_tools));
// 	tkn_list = tokeniser(str, shell);

// 	tmp = *tkn_list;
// 	while (tmp != NULL)
// 	{
// 		printf("Token Content: %s\nToken ID: %d\n",tmp->content, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	printf("No. of Pipes: %d\nNo. of Redirections: %d\n", shell->number_of_pipes, shell->number_of_redir);
// 	free(tkn_list);
// 	free(shell);
// 	return (0);
// }

// int	main(int argc, char **argv) //Testing skip quotation marks in args
// {
// 	t_tools	*shell;
// 	t_token	**tkn_list;
// 	t_token	*tkn;

// 	if (argc < 2)
// 		exit(1);
// 	shell = ft_calloc(1, sizeof(t_tools));
// 	tkn_list = tokeniser(argv[1], shell);
// 	tkn = *tkn_list;
// 	while (tkn != NULL)
// 	{
// 		printf("Tokens content is %s\nTokens_id is %d\n", tkn->content, tkn->type);
// 		tkn = tkn->next;
// 	}
// 	return (0);

// }
