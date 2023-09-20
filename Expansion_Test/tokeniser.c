#include "../../include/minishell.h"

t_token **tokeniser(char *input, t_tool *shell)
{
	t_token	**tkn_list;
	t_token	*tkn;
	char	**split_input;
	int		i;

	i = 0;
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
		{	
			assign_token_type(tkn, split_input[i]);
			tkn->content = get_literal_token(split_input[i]);
		}
		if (tkn->type == PIPE)
			shell->number_of_pipes += 1;
		if (tkn->type > 2)
			shell->number_of_redir += 1;
		add_token_back(tkn_list, tkn);
		i++;
	}
	return (tkn_list);
}

// int	main()
// {
// 	t_token	**tkn_list;
// 	t_token	*tmp;
// 	t_tool	*shell;
// 	char	*str;

// 	str = "ls -la < out";
// 	shell = ft_calloc(1, sizeof(t_tool));
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
// 	t_tool	*shell;
// 	t_token	**tkn_list;
// 	t_token	*tkn;

// 	if (argc < 2)
// 		exit(1);
// 	shell = ft_calloc(1, sizeof(t_tool));
// 	tkn_list = tokeniser(argv[1], shell);
// 	tkn = *tkn_list;
// 	while (tkn != NULL)
// 	{
// 		printf("Tokens content is %s\nTokens_id is %d\n", tkn->content, tkn->type);
// 		tkn = tkn->next;
// 	}
// 	return (0);

// }
