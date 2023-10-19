#include "../../include/minishell.h"

t_token	**build_tkn_list(char *input, t_token ***tkn_list);

t_token *init_token(char *content);

char* 	ft_strndup(const char* s, size_t n);


t_token **new_tokeniser(t_tools *shell)
{
	char	*tkn_string;
	t_token	**tkn_list;
	
	tkn_string = ft_strtrim(shell->input, " ");
	if (!tkn_string)
		return (NULL);
	tkn_list = ft_calloc(1, sizeof(t_token *));
	if (!tkn_list)
		return (free(tkn_string), NULL);
	tkn_list = build_tkn_list(tkn_string, &tkn_list);	
	return (tkn_list);
}

t_token **build_tkn_list(char *input, t_token ***tkn_list)
{
	t_token	*tkn;
	int		in_single_q;
	int		i;
	int		start;

	i = 0;
	start = -1;
	in_single_q = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_single_q)
		{	
			in_single_q = 1;
			start = i + 1;
		}
		else if (input[i] == '\'' && in_single_q)
		{	
			in_single_q = 0;
			tkn = init_token(ft_strndup(input + start, i - start));
			add_token_back(*tkn_list, tkn);
			start = -1;
		}
		else if (input[i] == ' ' && !in_single_q && start != -1)
		{	
			tkn = init_token(ft_strndup(input + start, i - start));
			add_token_back(*tkn_list, tkn);
			start = -1;
		}
		else if (!in_single_q && start == -1 && input[i] != ' ')
			start = i;
		i++;
	}
	if (start != -1)
	{	
		tkn = init_token(ft_strdup(input + start));
		add_token_back(*tkn_list, tkn);
	}
	return (*tkn_list);
}

t_token *init_token(char *content) 
{    
	t_token *tkn;
	int		i; 
	
	i = 0;
	tkn = (t_token *)ft_calloc(1, sizeof(t_token));
	if (is_redirection(content[i]))
	{	
		tkn->content = NULL;
		assign_token_type(tkn, content);
	}
    else
	{	
		tkn->content = ft_strdup(content);
		tkn->type = 2;
	}
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