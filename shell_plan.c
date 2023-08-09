
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
		
		+ The users input which will direct our programs behaviour.
		+ An array of strings which imports environment variables from the current users system.
		+ A data structure for the type t_command which stores command information needed by the executor to run commands.
		+ The number of pipes found in the users input to inform the executor how the command should be run. 
		
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
	
	We need to store all of these tokens with their own space in a data structure. We will choose to store them in a linked list. A
	linked list(simply put) is a series of nodes which in this implmentation will each hold:
		
		+ The content of the node as a string or NULL
		+ The token_id as an int
		+ A t_token pointer to the next node of the token_list
	
	---------------------------------------------------------TOKENISER------------------------------------------------------------------
	
	t_token **tokeniser(char *input, t_tool *shell)
	
	eg. "ls -la | cat >> output.txt"
	
	We will pass to the tokeniser our users input as a string and a pointer to our shell structure
	
	Firstly we will divide our string of arguments using ft_split with " " as the delimiter producing an array of strings:
	
			|1|	   |2| |3|  |4|  |5|     |6| 
			 |      |   |    |    |       |
			"ls" "-la" "|" "cat" ">>" "output.txt"
			
	If we initialise a linked list of tokens we can begin adding nodes from the back of the list.
	Adding nodes, involves allocating memory for each node which is a t_token struct.
	
	We then can begin to check what sort of information we have in the node. If we have alphabetical characters or a "-" 
	(the beginning of a flag) then we can say that we are dealing with a LITERAL token. LITERAL tokens can be commands,
	flags, arguments and file/or directory names.They also have a token_id of 2.
	
	Now to add the first token:
	
		+ Intialise our t_token	**tkn_list
		+ Intialise a t_token *tkn
		+ Initialise a char **array_of_strings
		+ Initialise an int i for indexing
	
	We can allocate memory for our tkn_list and for our tkn. ft_split will allocate memory for our array_of_strings.
	Iterating through our array_of_strings using i we can say:
	
		+ if (ft_isalpha(array_of_strings[i][0]) || array_of_strings[i][0] == '-' )
			
			tkn->content = use a function which will allocate space for a char * and then copy it from array_of_string[i][0];
			tkn->type = 2; 
		  
		  else if (array_of_strings[i][0] == '|' || '>' || '>>' || '<' || '<<')
		  {	 
		  	Use assign_token_type(t_token tkn, char * array_of_strings[i]) which takes users input and assigns the corresponding
		  	ENUM value as the token_id 

		  	if (the symbol is a PIPE)

		  		shell->number_of_pipes += 1;
		  }

	
	Now that all tokens stored in a list, we have the means necessary to build our t_command struct(s).
	
------------------------------------------------------------CREATE_COMMANDS-------------------------------------------------------------
	
	typedef struct	s_command
	{
		char				**args;
		t_redirection		*redirection;
		struct s_command	*next;
	}	t_command;
	
	typedef struct s_redirection
	{
    	char					*file_name;
    	t_token_type			type;
    	struct s_redirection	*next;
	}	t_redirection;


	t_command nodes will consist of an array of strings (**args) which contains its arguments. 

	RULES ABOUT **args

		+ args[0] will always be our command name 
		+ any argument which follows a PIPE will be a command name
		+ any argument after ">" must alphanumeric, i.e to assign or relate a file name
		+ any argument after ">>" must be alphanumeric, i.e to assign or relate a file name
		+ any argument after "<" must alphanumeric && an existing file in the current directory. 
	  
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
				+ If file doesnt exist, new file is created.
				
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
						
				+ If the filename doesnt exist. Error
		
		* If token_id == 6
		
				+ Next argument is expected to be a delimiter
				+ If not then error?
		
		int	i;
		
		i = 0;
		
		if (tmp->content)
			command->args[i] = tmp->content;
		else if (!(tmp->content)
			command->args[i] = convert_tkn_id_to_char(tmp->type);
	 
		
		
		
		
		
		QUESTIONS
		
		+	Why do we create a command_list? Is this only for when we have a PIPE?
		
		
		
		
		
		
		
		
		
		
		
		
		
		