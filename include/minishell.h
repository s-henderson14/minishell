#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdlib.h>
# include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>

//we ll define it later in the program
extern int g_sig;

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
    char            *file_name;
    char    *token_name;
    t_token_type    type; //if it s <<, heredoc, call heredoc f()
    struct s_redirection *next; //ls > output.txt < input.txt
                                //just like above, we might have multiple redir. in a command,
                                //thats why we have a pointer to redirection.
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
    int number_of_redir;
}t_tools;


typedef struct s_env_node
{
    struct s_env_node    *next;
    char            *key;
    char            *value;
}   t_env_node;

//main.c


//**PARSER**//

t_command   **parser(t_tools *shell);

//**TOKENISER**//

t_token     **tokeniser(char *input, t_tools *shell);

int         count_tokens(t_token **tkn_list);

char        *convert_tkn_id(int tkn_id);

char        *get_literal_token(char *input);

void        assign_token_type(t_token *tkn, char *str);

void        add_token_front(t_token **tkn_lst, t_token *new_tkn);

void        add_token_back(t_token **tkn_lst, t_token *new_tkn);

//**CREATE COMMANDS**//

t_command   **create_simple_cmd(t_token **tkn_list, t_tools *shell);

t_command   **create_adv_cmd(t_token **tkn_list, t_tools *shell);

void        add_cmd_front(t_command **cmd_lst, t_command *new_cmd);

void        add_cmd_back(t_command **cmd_lst, t_command *new_cmd);

int         word_counter(const char *s, char c);

//**REDIRECTIONS**//

void        redir_init(t_command *cmd, t_token *tkn);

void	    add_redir_back(t_redirection *redir_lst, t_redirection *new_redir);

void	    add_redir_front(t_redirection *redir_lst, t_redirection *new_redir);

int count_nodes(t_redirection *redirection);

//**EXPANSION**//

int         double_found(char *str);

int         dollar_sign_found(char *string);

//int         check_key_exists(char *key, t_env_node *env_list);

//int         ft_strsame(const char *s1, const char *s2);

//char        *get_value_from_env_node(char *key, t_env_node *env_list);

char        *expand(char *input, t_env_node*env_list);

//test.c
void    init_command_structure(int argc, char **argv, t_tools *tools);
t_command *init_command_list(char *line, t_tools *tools);
void    malloc_command_list_structure(t_tools *tools);
char **copy_content_until_pipe(char **args, int *pipe_index_position);
int count_pipes(char **argv);
int count_args_until_pipe(char **args, int i);
int count_args(char **args);

//test_redirection.c
//int check_redirection_exist(t_command *command);
int check_redirection_exist(char **command_args);
void decide_redirection_type(t_redirection *redirection);
t_redirection *init_redirection(t_command *command);


//env.c
t_env_node *init_env_linked_list(char **env);
t_env_node *env_node_create(char *key, char *value);
char *get_key_from_env_arr(char *env_str);
char *get_value_from_env_arr(char *env_str);
void change_value_of_env_key(char *new_value, char *key, t_env_node *env_list);


//env_utils.c
void env_list_print(t_env_node *env_list);
int env_list_size(t_env_node *env_list);
int env_str_arr_size(char **env);
void env_node_add_back(t_env_node *new_node, t_env_node *env_list);
void env_node_free(t_env_node *node);
void env_list_free(t_env_node *env_list);

//env_utils_2.c
void print_value(char *key, t_tools *tools);
int check_key_exist(char *key, t_env_node *env_list);
void free_key_and_value(char *key, char *value);
void remove_oldpwd(t_env_node *env_list);


//UTILS
//utils.c
int error_exit(char *s, int exit_status);
char *protect(char *arg);
char **argv_duplicate_without_program_name(char **argv, int argc);
char **array_dup(char **env);

//utils_list.c
void    ft_lstadd_back_command(t_command *command_list, t_command *command);
t_command   *ft_lstnew_command(char **dup, t_tools *tools);
t_command   *init_single_command(t_tools *tools, char **temp_args);
void command_list_free(t_command *command_list);
void    free_double_arr(char **arr);


//BUILTINS
//mini_cd.c
void    initiate_oldpwd(char *value_to_oldpwd, t_env_node *env_list);
char *find_upper_dir(char *current_dir);
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

//mini_exit.c
int mini_exit(t_tools *tools, t_command *command);

//mini_unset.c
void find_node_in_list_remove(char *key, t_env_node *env_list);
int mini_unset(t_tools *tools, t_command *command);

//mini_export.c
t_env_node *split_arg_and_create_node(char *arg);
int mini_export(t_tools *tools, t_command *command);
void    print_env_for_export(t_env_node *env_list);

//builtin_utils.c
int find_equal_sign(char *arg);
int check_arg_digit(char *arg);
int is_builtin(t_command *command);



//EXECUTE
//redirections.c
void protected_dup2(int old_fd, int new_fd);
int input_redirection(t_redirection *redirection);
int output_redirection(t_redirection *redirection);
int redirection(t_command *command);

//heredoc.c
void check_heredoc(t_command *command);
//void here_document(char *delimiter, char *temp_file);
void here_document(t_command *command, t_redirection *redirection);

//execute.c
void simple_command_no_pipe(t_tools *tools, t_command *command_list);
void execute_without_pipe(t_tools *tools);
void execute(t_tools *tools);
int exec_builtin(t_tools *tools);

//execute_utils.c
char *join_command_to_path(char *path, char *main_command);
char **get_paths(t_tools *tools);
int call_execve(t_tools *tools, t_command *command);

//handle_pipes.c
void handle_pipes(t_tools *tools);
void single_execution_in_pipe(t_tools *tools, t_command *command, int *fd_input, int fd[]);
void child_exec_in_pipe(t_tools * tools, t_command *command, int *fd_input, int fd[]);
int last_command_execution(t_tools * tools, t_command *command, int *fd_input, int fd[]);
int	latest_status(pid_t pid, int pipe_num);


//EXPAND
//expand_dollar_sign.c
int check_first_char_dollar(char *string);
char *expand_string(char *string, t_tools *tools);


//SIGNALS
void signal_handler(int signum);
void signal_child(void);
void signal_parent(void);
void signal_init(void);
void signal_noninteractive(void);

#endif