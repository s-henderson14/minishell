#include "../include/minishell.h"

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