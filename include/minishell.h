#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>

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


//env.c
t_env_node *init_env_linked_list(char **env);
t_env_node *env_node_create(char *key, char *value);
char *get_key_from_env_arr(char *env_str);
char *get_value_from_env_arr(char *env_str);
void change_value_of_env_key(char *new_value, t_env_node *env_list);


//env_utils.c
void env_list_print(t_env_node *env_list);
int env_list_size(t_env_node *env_list);
void env_node_add_back(t_env_node *new_node, t_env_node *env_list);
void env_node_free(t_env_node *node);
void env_list_free(t_env_node *env_list);


#endif