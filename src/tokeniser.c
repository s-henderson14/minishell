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
	if (str == GREAT_GREAT)
		tkn->type =  GREAT_GREAT;
	else if (str == LESS_LESS)
		tkn->type = LESS_LESS;
	else if (str == GREAT)
		tkn->type = GREAT;
	else if (str == LESS)
		tkn->type = LESS;
	else if (str == PIPE)
		tkn->type = PIPE;
}

t_token **tokeniser(char *input)
{
	t_token	**tkn_list;
	t_token	*tkn;
	char	**split_input;
	int		start;

	start = 0;
	tkn_list = ft_calloc(1, sizeof(t_token *));
	split_input = ft_split(input, ' ');
	if (split_input[start] == NULL)
		return (NULL);
	while (split_input[start])
	{	
		tkn = ft_calloc(1, sizeof(t_token));
		if(ft_isprint(split_input[start][0]))
		{	
			tkn->type = LITERAL;	
			tkn->content = get_literal_token(split_input[start]);
			add_token_back(tkn_list, tkn);
			start++;
		}
		else
			assign_token_type(tkn, split_input[start]);
		add_token_back(tkn_list, tkn);
		start++;
	} 
	return (tkn_list);
}

int	main(int argc, char **argv)
{
	(void)argc;
	tokeniser(argv[1]);
	return (0);
}
