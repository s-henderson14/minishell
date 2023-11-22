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

void	assign_token_type(t_token *tkn, char *str, t_tools *shell)
{
	if (ft_strlen(str) == 2)
	{	
		if (str[0] == '>')
			tkn->type =  GREAT_GREAT;
		else if (str[0] == '<')
			tkn->type = LESS_LESS;
		shell->number_of_redir += 1;	
	}
	if (ft_strlen(str) == 1)
	{	
		if (str[0] == '>')
			tkn->type = GREAT;
		if (str[0] == '<')
			tkn->type = LESS;
		shell->number_of_redir += 1;
	}
	if (str[0] == '|')
	{	
		tkn->type = PIPE;
		shell->number_of_pipes += 1;
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

void	init_lexer_state(t_machine *lexer)
{
	lexer->insingleq = 0;
	lexer->indoubleq = 0;
	lexer->start = -1;
}

void	check_single_quote(t_machine *lexer, t_tools *shell, int *index)
{
	if (shell->input[*index] == '\'' && !lexer->insingleq && !lexer->indoubleq)
	{	
		lexer->insingleq = 1;
		lexer->start = *index + 1;
	}
}

void	close_single_quote(t_machine *lexer, t_token *tkn, t_tools *shell, int *index)
{
	if (shell->input[*index] == '\'' && lexer->insingleq)
	{	
		lexer->insingleq = 0;
		tkn = init_token(ft_strndup(shell->input + lexer->start, *index - lexer->start), shell);
		add_token_back(shell->tkn_list, tkn);
		lexer->start = -1;
	}
}

void	handle_double_quote(t_machine *lexer, t_token *tkn, t_tools *shell, int *index)
{
	if (shell->input[*index] == '"' && !lexer->insingleq && !ft_strchr(shell->input + lexer->start, '='))
	{	
		if (lexer->indoubleq && lexer->start != -1)
		{	
			tkn = init_token(ft_strndup(shell->input + lexer->start, *index - lexer->start), shell);
			add_token_back(shell->tkn_list, tkn);
			lexer->start = -1;
		}
		toggle_double_quote(lexer, &index);
	}
}

void	toggle_double_quote(t_machine *lexer, int **index)
{
	lexer->indoubleq = !lexer->indoubleq;
	if (lexer->indoubleq)
		lexer->start = (**index) + 1;	
}

void	handle_expansion(t_machine *lexer, t_token *tkn, t_tools *shell, int *index)
{
	if (shell->input[*index] == '$' && !lexer->insingleq)
	{
		tkn = init_token(expand(ft_strndup(shell->input + *index + 1 ,word_len(shell->input, *index + 1)), shell->env_list), shell);
		add_token_back(shell->tkn_list, tkn);
		*index = *index + word_len(shell->input, *index);
		lexer->start = -1;
	}
}

void	redir_tokens(t_machine *lexer, t_token *tkn, t_tools *shell, int *index)
{
	if (shell->input[*index + 1] == '>' || shell->input[*index + 1] == '<')
	{	
		tkn = init_token(ft_strndup(shell->input + *index + 1, 2), shell);
		add_token_back(shell->tkn_list, tkn);
		*index += 2;
	}
	else if (shell->input[*index] == '>' || shell->input[*index] == '<')
	{	
		tkn = init_token(ft_strndup(shell->input + *index, 1), shell);
		add_token_back(shell->tkn_list, tkn);
	}
	lexer->start = -1;
}

void	add_last_token(t_machine *lexer, t_token *tkn, t_tools *shell)
{
	if (lexer->start != -1)
	{	
		tkn = init_token(ft_strdup(shell->input + lexer->start), shell);
		add_token_back(shell->tkn_list, tkn);
	}
}

int	tkn_delimiter_found(t_machine *lexer, t_token *tkn, t_tools *shell, int *index)
{
	if ((shell->input[*index] == ' ' || shell->input[*index] == '>' || shell->input[*index] == '<' || shell->input[*index] == '|')
		&& !lexer->insingleq && !lexer->indoubleq && lexer->start != -1)
	{
		tkn = init_token(ft_strndup(shell->input + lexer->start, *index - lexer->start), shell);
		add_token_back(shell->tkn_list, tkn);
		return (1);
	}
	return (0);
}