#include "../../include/minishell.h"

t_token *build_tkn_list(char *input, t_tools *shell)
{
	t_token		*tkn;
	t_machine	*lexer;
	int			i;

	i = 0;
	init_lexer_state(lexer);
	while (input[i])
	{
		if (input[i] == '\'' && !lexer->insingleq && !lexer->indoubleq)
			start_single_quote(lexer, &i);
		else if (input[i] == '\'' && lexer->insingleq)
		{	
			close_single_quote(lexer, tkn, shell, &i);
			add_token_back(shell->tkn_list, tkn);
		}
		else if (input[i] == '"' && !lexer->insingleq && !ft_strchr(input + lexer->start, '=')) // Handle double quotes
		{
			if (lexer->indoubleq && lexer->start != -1)
			{
				handle_double_quote(lexer, tkn, shell, &i);
				add_token_back(shell->tkn_list, tkn);
			}
			toggle_double_quote(lexer, &i);
		}
		else if (input[i] == '$' && !lexer->insingleq)
		{	
			handle_expansion(lexer, tkn, shell, &i);
			add_token_back(shell->tkn_list, tkn);
		}
		else if ((input[i] == ' ' || input[i] == '>' || input[i] == '<' || input[i] == '|')
		&& !lexer->insingleq && !lexer->indoubleq && lexer->start != -1)
		{	
			tkn = init_token(ft_strndup(input + lexer->start, i - lexer->start), shell);
			add_token_back(shell->tkn_list, tkn);
			if (redir_tokens == 1)
				add_token_back(shell->tkn_list, tkn);
		}
		else if (!lexer->insingleq && !lexer->indoubleq && lexer->start == -1 && input[i] != ' ')
			lexer->start = i;
		i++;
	}
	if (lexer->start != -1)
		add_last_token(lexer, tkn, shell);
	return (shell->tkn_list);
}