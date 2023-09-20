#include "../../include/minishell.h"

char	*get_literal_token(char *input)
{
	int		i;
	int		j;
	char	*literal;

	i = 0;
	j = 0;
	literal = malloc(ft_strlen(input) + 1);
	while (input[j])
	{	
		while (input[j] == 34 || input[j] == 39)
			j++;	
		literal[i] = input[j];
		i++;
		j++;
	}
	literal[i] = '\0';
	return (literal);
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

char	*convert_tkn_id(int tkn_id)
{
	char	*symbol;

	if (tkn_id % 2 == 1)
		symbol = ft_calloc(1, sizeof(char));
	else
		symbol = ft_calloc(2, sizeof(char));
	if (tkn_id == 1)
		symbol = "|";
	else if (tkn_id == 3)
		symbol = ">";
	else if (tkn_id == 5)
		symbol = "<";
	else if (tkn_id == 4)
		symbol = ">>";
	else if (tkn_id == 6)
		symbol = "<<";
	return (symbol);	
}