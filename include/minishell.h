#ifndef MINISHELL_H
# define MINISHELL_H
#endif

# include "../libft/libft.h"

extern int glob_exit_status; //with extern, we declare glob_exit_status without defining
//we ll define it later in the program

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
}t_redirection;

typedef struct s_command
{
    char **args;
    t_redirection *redirection;
    struct s_command *next;
}t_command;


typedef struct s_tools
{
    char *input;
    char **env;
    struct s_env_node *env_list;
    t_command *command_list;
   // t_token *history;
    int number_of_pipes;

}t_tools;


typedef struct s_env_node
{
    struct s_env_node    *next;
    char            *key;
    char            *value;
}   t_env_node;

