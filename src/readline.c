// #include "../include/minishell.h"
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// static char *input_buf = NULL;



// int	main()
// {	
// 	char cwd_buf[250];
	
// 	while (1)
// 	{	
// 		if(input_buf)
// 		{
// 			free(input_buf);
// 			input_buf = NULL;
// 		}
// 		if (cwd_buf[0])
// 			ft_bzero(cwd_buf, sizeof(cwd_buf));
// 		getcwd(cwd_buf, sizeof(cwd_buf));
// 		printf("%s/", cwd_buf);
// 		input_buf = readline("GoSh: ");
// 		if (strlen(input_buf) > 0)
// 			add_history(input_buf);
// 		if (strcmp(input_buf, "exit") == 0)
// 			break ;
// 	}
// 	return (0);
// }
