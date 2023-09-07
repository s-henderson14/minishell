#ifndef MINISHELL_H
# define MINISHELL_H
#endif

# include "../libft/libft.h"
# include <stdio.h>

extern int glob_exit_status; //with extern, we declare glob_exit_status without defining
//we ll define it later in the program

/*depending on the sign, we'll assing it to a token_type.
if we have a < then it ll be LESS, (input_redirection)
if we have a cd or ls or any other command-like thing, it ll be LITERAL,
if we have a >> then it is GREAT_GREAT, (output_redirection but appends)
etc.
*/

typedef enum s_token_type
{
    PIPE = 1,
    LITERAL,
    GREAT,
    GREAT_GREAT,
    LESS,
    LESS_LESS,
}   t_token_type;

typedef struct s_token
{
    char            *content;
    t_token_type    type;
    struct s_token  *next;
}   t_token;


typedef struct s_redirection
{
    char            *file_name; //if it s <<, heredoc, call heredoc f()
    t_token_type    type;
    struct s_redirection *next;
}	t_redirection;

typedef struct s_command
{
    char **args;
    t_redirection *redirection;
    struct s_command *next;
}	t_command;


typedef struct s_tools
{
    char *input;
    char **env;
    struct s_env_node *env_list;
    struct t_command *command_list;
   // t_token *history;
    int number_of_pipes;
	int	number_of_redir;

}	t_tool;


typedef struct s_env_node
{
    struct s_env_node    *next;
    char            *key;
    char            *value;
}   t_env_node;

//**PARSER**//

t_command	**parser(t_tool *shell);

//**TOKENISER**//

t_token 	**tokeniser(char *input, t_tool *shell);

int 		count_tokens(t_token **tkn_list);

char		*convert_tkn_id(int tkn_id);

//**CREATE COMMANDS**//

t_command	**create_simple_cmd(t_token **tkn_list, t_tool *shell);

t_command	**create_adv_cmd(t_token **tkn_list, t_tool *shell);

//**REDIRECTIONS**//

void		redir_init(t_command *cmd, t_token *tkn, int *index);

//**EXPANSION**//

int			meta_found(char *str);

int 		dollar_sign_found(char *string);

int 		check_key_exists(char *key, t_env_node *env_list);

int			ft_strsame(const char *s1, const char *s2);

char		*get_value_from_env_node(char *key, t_env_node *env_list);