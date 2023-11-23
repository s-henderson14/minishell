#include "../../include/minishell.h"

//t_token	*build_tkn_list(char *input, t_token ***tkn_list, t_tools *shell);
//t_token *build_tkn_list(char *input, t_tools *shell);

t_token *init_token(char *content, t_tools *shell);

char* 	ft_strndup(const char* s, size_t n);


t_token *new_tokeniser(t_tools *shell)
{
	t_machine	*lexer;
	
	lexer = ft_calloc(1, sizeof(t_machine));
	build_tkn_list(lexer,shell);
	return (shell->tkn_list);
}

// t_token *build_tkn_list(t_machine *lexer, t_tools *shell)
void	build_tkn_list(t_machine *lexer, t_tools *shell)
{
	t_token		*tkn;
	int			i;

	i = 0;
	tkn = ft_calloc(1, sizeof(t_token));
	shell->tkn_list = ft_calloc(1, sizeof(t_token));
		if (!shell->tkn_list)
			return ;
	init_lexer_state(lexer);
	while (shell->input[i])
	{
		check_single_quote(lexer, shell, &i);
		close_single_quote(lexer, tkn, shell, &i);
		handle_double_quote(lexer, tkn, shell, &i);
		handle_expansion(lexer, tkn, shell, &i);
		if (tkn_delimiter_found(lexer, tkn, shell, &i))
			redir_tokens(lexer, tkn, shell, &i);
		if (!lexer->insingleq && !lexer->indoubleq && lexer->start == -1 && shell->input[i] != ' ')
			lexer->start = i;
		i++;
	}
	add_last_token(lexer, tkn, shell);
}

// t_token *build_tkn_list(t_tools *shell)
// {
// 	t_token	*tkn;
// 	int		in_single_q;
// 	int		in_double_q;
// 	int		i;
// 	int		start;

// 	i = 0;
// 	start = -1;
// 	in_single_q = 0;
// 	in_double_q = 0;
// 	while (shell->input[i])
// 	{
// 		if (shell->input[i] == '\'' && !in_single_q && !in_double_q)
// 		{	
// 			in_single_q = 1;
// 			start = i + 1;
// 		}
// 		else if (shell->input[i] == '\'' && in_single_q)
// 		{	
// 			in_single_q = 0;
// 			tkn = init_token(ft_strndup(shell->input + start, i - start), shell);
// 			add_token_back(shell->tkn_list, tkn);
// 			start = -1;
// 		}
// 		else if (shell->input[i] == '"' && !in_single_q && !ft_strchr(shell->input + start, '=')) // Handle double quotes
// 		{
// 			if (in_double_q && start != -1)
// 			{
// 				tkn = init_token(ft_strndup(shell->input + start, i - start), shell);
// 				add_token_back(shell->tkn_list, tkn);
// 				start = -1;
// 			}
// 			in_double_q = !in_double_q;
// 			if (in_double_q)
// 				start = i + 1;
// 		}
// 		else if (shell->input[i] == '$' && !in_single_q)
// 		{
// 			tkn = init_token(expand(ft_strndup(shell->input + i + 1 ,word_len(shell->input, i + 1)), shell->env_list), shell);
// 			add_token_back(shell->tkn_list, tkn);
// 			i = i + word_len(shell->input, i);// - 1; //removed to fix error with command sequence (1)export var=a (2) export $var=test
// 			start = -1;
// 		}
// 		else if ((shell->input[i] == ' ' || shell->input[i] == '>' || shell->input[i] == '<' || shell->input[i] == '|')
// 		&& !in_single_q && !in_double_q && start != -1)
// 		{
// 			tkn = init_token(ft_strndup(shell->input + start, i - start), shell);
// 			add_token_back(shell->tkn_list, tkn);
// 			if (shell->input[i + 1] == '>' || shell->input[i + 1] == '<')
// 			{
// 				tkn = init_token(ft_strndup(shell->input + i + 1, 2), shell);
// 				add_token_back(shell->tkn_list, tkn);
// 				i += 2;
// 			}
// 			else if (shell->input[i] == '>' || shell->input[i] == '<')
// 			{
// 				tkn = init_token(ft_strndup(shell->input + i, 1), shell);
// 				add_token_back(shell->tkn_list, tkn);
// 			}
// 			start = -1;
// 		}
// 		else if (!in_single_q && !in_double_q && start == -1 && shell->input[i] != ' ')
// 			start = i;
// 		i++;
// 	}
// 	if (start != -1)
// 	{
// 		tkn = init_token(ft_strdup(shell->input + start), shell);
// 		add_token_back(shell->tkn_list, tkn);
// 	}
// 	return (shell->tkn_list);
// }

t_token *init_token(char *content, t_tools *shell)
{
	t_token *tkn;
	int		i;

	i = 0;
	tkn = (t_token *)ft_calloc(1, sizeof(t_token));
	if (is_redirection(content[i]))
	{
		tkn->content = NULL;
		assign_token_type(tkn, content, shell);
	}
    else
	{
		tkn->content = ft_strdup(content);
		tkn->type = 2;
	}
	//printf("token in init_token = %s\n", tkn->content);
    tkn->next = NULL;

    return (tkn);
}

char* ft_strndup(const char* s, size_t n) 
{    
	size_t	len;
	char* 	new_str;
	
	len = ft_strlen(s);
	if (n < len) 
        len = n;
    new_str = (char*) malloc(len + 1);
    if (new_str == NULL) 
        return (NULL);
    ft_memcpy(new_str, s, len);
    new_str[len] = '\0';
    return (new_str);
}

int	is_redirection(char input)
{
	if (input == '|')
		return (1);
	else if (input == '>')
		return (1);
	else if (input == '<')
		return (1);
	return (0);
}

int	word_len(char *str, int start)
{	
	int	len;
	
	len = 0;
	if (!str[start])
		return (0);
	while (str[start])
	{ 
		if (str[start] == ' ' || str[start] == 34 || str[start] == 39 || str[start] == '=')
			break;
		len++;
		start++;
	}
	return (len);
}
// t_token *tokenise(const char *s, char delimiter) {
    
// 	int i;
//     int token_start;
//     int isInQuote;
//     t_token *head;
	
// 	i = 0;
// 	token_start = -1;
// 	isInQuote = 0;
// 	head = NULL;
//     while (s[i]) {
//         if (s[i] == '\'' && !isInQuote) 
// 		{
//             isInQuote = 1;
//             token_start = i + 1;
//         } 
// 		else if (s[i] == '\'' && isInQuote)
//         {   
// 			isInQuote = 0;
//             append_token(&head, strndup(s + token_start, i - token_start));
//             token_start = -1;
// 		}
//         else if (s[i] == delimiter && !isInQuote && token_start != -1)
//         {	
// 			append_token(&head, strndup(s + token_start, i - token_start));
//             token_start = -1;
// 		}
//         else if (!isInQuote && token_start == -1 && s[i] != delimiter)
//             token_start = i;
//         i++;
//     }
//     if (token_start != -1)
//         append_token(&head, strdup(s + token_start));
//     return head;
// }