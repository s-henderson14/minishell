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

}	t_tool;


typedef struct s_env_node
{
    struct s_env_node    *next;
    char            *key;
    char            *value;
}   t_env_node;

t_token **tokeniser(char *input);

int count_tokens(t_token **tkn_list);

char	*convert_tkn_id(int tkn_id);

t_command   *create_cmds(t_token **tkn_list);
/*
ALSO WE ARE ALLOWED TO USE ONE SINGLE GLOBAL VARIABLE
Maybe we could use a int glob_exit_status
it makes implementing expansion of $? easier.

our function to be called is: my_func()
Imagine that we store the exit status of my_func() in glob_exit_status,
after the execution of my_func(), we have the shell prompt back,
when we call $? in shell, 
we reach the exit status of most recent function call which is 'glob_exit_status'

*/