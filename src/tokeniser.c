#include "../include/minishell.h"

char	*get_literal_token(char *input)
{
	int		i;
	char	*literal;

	i = 0;
	literal = malloc(ft_strlen(input) + 1);
	while (input[i])
	{	
		literal[i] = input[i];
		i++;
	}
	literal[i] = '\0';
	return (literal);
}

void	add_token_front(t_token **tkn_lst, t_token *new_tkn)
{
	new_tkn->next = *tkn_lst;
	*tkn_lst = new_tkn;
}

void	add_token_back(t_token **tkn_lst, t_token *new_tkn)
{
	t_token	*tmp;

	tmp = *tkn_lst;
	if (*tkn_lst == NULL)
	{	
		add_token_front(tkn_lst, new_tkn);
		return ;
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_tkn;
}

void	assign_token_type(t_token *tkn, char *str)
{
	if (ft_strlen(str) == 2)
	{	
		if (str[0] == '>')
			tkn->type =  GREAT_GREAT;
		else if (str[0] == '<')
			tkn->type = LESS_LESS;
	}
	if (ft_strlen(str) == 1)
	{	
		if (str[0] == '>')
			tkn->type = GREAT;
		if (str[0] == '<')
			tkn->type = LESS;
		if (str[0] == '|')
			tkn->type = PIPE;
	}
}

t_token **tokeniser(char *input)
{
	t_token	**tkn_list;
	t_token	*tkn;
	char	**split_input;
	int		start;

	start = 0;
	tkn_list = ft_calloc(1, sizeof(t_token *));
	if (!tkn_list)
		return (NULL);
	split_input = ft_split(input, ' ');
	if(!split_input)
		return (free(tkn_list), NULL);
	while (split_input[start])
	{	
		tkn = ft_calloc(1, sizeof(t_token));
		if (!tkn)
		{
			//clean split()
			//free list()
			//return(NULL);
		}
		if(ft_isalpha(split_input[start][0]) || split_input[start][0] == 45)
		{	
			tkn->type = LITERAL;	
			tkn->content = get_literal_token(split_input[start]);
			add_token_back(tkn_list, tkn);
			start++;
		}
		else
		{	
			assign_token_type(tkn, split_input[start]);
			add_token_back(tkn_list, tkn);
			start++;
		}
	}
	return (tkn_list);
}

// int	main(int argc, char **argv)
// {
// 	t_token	**tkn_list;
// 	t_token	*tmp;

// 	(void)argc;
// 	tkn_list = tokeniser(argv[1]);
// 	tmp = *tkn_list;
// 	while (tmp != NULL)
// 	{
// 		printf("Token Content: %s Token ID: %d\n",tmp->content, tmp->type);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }
