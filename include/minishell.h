#ifndef MINISHELL_H
# define MINISHELL_H
#endif

# include "../libft/libft.h"

typedef enum s_tokens
{
    PIPE = 1,
    GREAT,
    GREAT_GREAT,
    LESS,
    LESS_LESS,
}   t_tokens;

typedef struct s_token
{
    char            *content;
    int             token_id;
    struct s_token  *next;
}   t_token;


typedef struct s_tools
{
    char **env;
    struct s_env_var *env_var;
    struct s_command *command;
}t_tool;


typedef struct s_command
{
    char **args;




}t_command;

BUILTINS

typedef struct s_env_var
{
    struct s_env    *next;
    char            *key;
    char            *value;
}   t_env_var;

