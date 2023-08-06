	
	typedef enum s_token_type
	{
    	PIPE = 1,
    	LITERAL,
    	GREAT,
    	GREAT_GREAT,
    	LESS,
    	LESS_LESS,
	}	t_token_type;
	
	typedef struct	s_token
	{	
		char			*content;
		t_token_type	type;
		struct s_token	*next
	}	t_token
	
	typedef struct s_redirection
	{
    	char					*file_name;
    	t_token_type			type;
    	struct s_redirection	*next;
	}	t_redirection;
	
	typedef struct	s_command
	{
		char				**args;
		t_redirection		*redirection;
		struct s_command	*next;
	}	t_command;
	
	typedef struct s_tools
	{
    	char 	*input;
    	char 	**env;
    	struct	s_env_node *env_list;
    	struct	t_command *command_list;
    	int 	number_of_pipes;

	}	t_tool;
	
	-------------------------------------------------------LEXER & PARSER---------------------------------------------------------------
	
	We begin with our t_tool struct, this can be considered the main struct representing our shell program. It will be responsible for
	storing the following information:
		
		+ The user's input which will direct our programs behaviour.
		+ An array of strings which imports environment variables from the current user's system.
		+ A data structure for the type t_command which stores command information needed by the executor to run commands.
		+ The number of pipes found in the user's input to inform the executor how the command should be run. 
		
	Initialising space for the t_tool struct will involve memory allocation for:
	
		+ char		*input
		+ struct	s_env_node *env_list;
    	+ struct	t_command *command_list;
	
	-----------------------------------------------------------LEXER--------------------------------------------------------------------
	
	The Lexer part of the shell must read through the input given by the user. An example could be
	
		ls -la | cat >> output.txt
	
	The result of this command will list everything in the current directory and then use this output as the source to be concatenated
	to the file 'output.txt'.
	
	This input consists of 6 tokens:
	
		+ ls  -----------> A LITERAL token which will be recognised as a command because it is the first argument given.
		+ -la -----------> A LITERAL token which will be recognised as an argument because it follows the first command.
		+ |   -----------> A PIPE token with a token_id identified by an integer. tools->number_of_pipes += 1
		+ cat -----------> A LITERAL token which will be recongised as a command because a '|' token must be followed by a command.
		+ >>  -----------> A GREAT_GREAT token with a token_id for an output redirection.
		+ output.txt ----> A LITERAL token which be used to name a new file or identify an exisitng file to be overwritten.
	
	
	
	tkn_list = tokeniser(shell->input)
		
		+ tokeniser() creates a linked list of tokens from the char* input and stores it in the variable tkn_list.
	
	This list of t_token struct nodes have:
	 
		+ Each node has content either a string or null
		+ All nodes have a token_id
		+ All nodes have a pointer to the next or last node of the list.	
	
	Now we would like to pass each of those tokens to a t_command struct and store each of the tokens in our array of arguments.	
	
	  
	* Create a pointer to a t_token node and call it tmp;
		
		t_token	*tmp;
		
	* Set it equal to the first node of the tkn_list;

		tmp = *tkn_list;
	
	* While we are not at the end of our tkn_list
	
		while (tmp != NULL)
	
	
	* If tkn->content is not NULL, add this string to the t_command array of args. Note: ARG[0] will be the first command.
	
	
	* If there is no content, then we have a redirection.
	
		* If the token_id == 1.
			
				+ Next argument must be a string which is also a recognised command.
				+ Note: Can also be a newline and then the next argument must be a string and a command.
				+ If the string is not recognised as a command then treat as an error. 
	
		* If token_id == 3
			
				+ Next argument is expected to be a string.	This will be the new or existing filename.
				+ Create a new file or overwrite an existing file. 
				+ Check: Are there any edge cases that is not allowed as a name?
		
		* If token_id == 4
				
				+ Next argument is expected to be a string. New or existing filename.
				+ If file exists, input is appended to file.
				+ If file doesn't exist, new file is created.
				
		* If token_id == 5
		
				+ Next argument is expected to be a string and this filename must already exist.
				+ Access() can be used to determine whether the file already exists.
					+ int access(const char *pathname, int mode);
					+ pathname - This is a string that specifies the path to the file you want to check.
					+ This is an integer that specifies what kind of access you want to check for.
						-	F_OK: Check for the existence of the file.
						-	R_OK: Check for read permission.
						-	W_OK: Check for write permission.
						-	X_OK: Check for execute permission.
					+ returns 0 if the requested access is allowed, and -1 otherwise.
						
				+ If the filename doesn't exist. Error
		
		* If token_id == 6
		
				+ Next argument is expected to be a delimiter
				+ If not then error?
		
		int	i;
		
		i = 0;
		
		if (tmp->content)
			command->args[i] = tmp->content;
		else if (!(tmp->content)
			command->args[i] = convert_tkn_id_to_char(tmp->type);
	 
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
