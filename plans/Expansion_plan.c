How does BASH handle quotations?


Using single quotation marks will mean the literal text is returned. Therefore there is not much to change

Using double quotations will also expand:

	+ $IF_ENV_VAR_EXISTS to the string stored in the env_var
	
	+ 	$ name="John"
		$ echo "Hello $name!"
		Hello John! 

In minishell we only have to handle the expansion of variables using $

HANDLE QUOTATIONS

	Single Quotations

		+ If reading user input and we find single quotes then this is no matter, carry on as before so long as there are an even amount of marks.
		
		+ If the count of single marks is uneven then we have to error because we dont handle this.

	Double Quotations

		+ If we are reading our input and find double quotes we should read to the end of the word and then check whether this word exists as an env_var in our env_list.
		+ We can check the variables existence using check_key_exist()
		+ If we find it then we will use our get_value_from_env_node()
		+ The value returned from get_value_from_env_node() will then be substituted as the argument in the token_list.

So what does an expansion look like?
	
	We have an input from the user which is stored in a t_toolsinstance as shell->input.

	We can first read through this and check if we have double quotation marks.
	Then we should check if we have an even number of marks, otherwise we should error

	If we have even number of marks, we should check within the marks for a $ dollar sign.
	If the dollar sign



