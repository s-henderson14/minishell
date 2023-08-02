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
    int number_of_pipes; //this +1 will give us number of command we have in command_list

}t_tools;


typedef struct s_env_node
{
    struct s_env_node    *next;
    char            *key;
    char            *value;
}   t_env_node;

//test.c
void    init_command_structure(char **argv, int argc, t_tools *tools);
void    malloc_command_list_structure(t_tools *tools);
void choose_builtin(char **argv, t_tools *tools);

//env.c
t_env_node *init_env_linked_list(char **env);
t_env_node *env_node_create(char *key, char *value);
char *get_key_from_env_arr(char *env_str);
char *get_value_from_env_arr(char *env_str);
void change_value_of_env_key(char *new_value, char *key, t_env_node *env_list);


//env_utils.c
void env_list_print(t_env_node *env_list);
int env_list_size(t_env_node *env_list);
void env_node_add_back(t_env_node *new_node, t_env_node *env_list);
void env_node_free(t_env_node *node);
void env_list_free(t_env_node *env_list);

//env_utils_2.c
void print_value(char *key, t_tools *tools);
int check_key_exist(char *key, t_env_node *env_list);


//utils.c
int error_exit(char *s);
char *protect(char *arg);
void    ft_lstadd_back_command(t_command *command_list, t_command *command);
t_command   *ft_lstnew_command(char **dup);
char **argv_duplicate_without_program_name(char **argv, int argc);



//BUILTINS
//mini_cd.c
void    initiate_oldpwd(char *value_to_oldpwd, t_env_node *env_list);
void set_pwd_update_oldpwd(char *new_path, t_env_node *env_list);
char  *get_value_from_env_node(char *key, t_env_node *env_list);
int mini_cd(t_tools *tools, t_command *command);

//mini_echo.c
void print_arguments(int i, t_tools *tools, t_command *command);
int mini_echo(t_tools *tools, t_command *command);

//mini_pwd.c
int mini_pwd(t_tools *tools);

//mini_env.c
int mini_env(t_tools *tools, t_command *command);


#endif